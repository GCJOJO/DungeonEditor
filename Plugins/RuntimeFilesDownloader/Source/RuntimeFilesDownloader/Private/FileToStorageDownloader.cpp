// Georgy Treshchev 2022.

#include "FileToStorageDownloader.h"
#include "RuntimeFilesDownloaderDefines.h"

#include "Misc/Paths.h"
#include "HAL/FileManager.h"
#include "HAL/PlatformFilemanager.h"
#include "GenericPlatform/GenericPlatformFile.h"


UFileToStorageDownloader* UFileToStorageDownloader::BP_DownloadFileToStorage(const FString& URL, const FString& SavePath, float Timeout, const FString& ContentType, const FOnSingleCastDownloadProgress& OnProgress, const FOnSingleCastFileToStorageDownloadComplete& OnComplete)
{
	UFileToStorageDownloader* Downloader{NewObject<UFileToStorageDownloader>(StaticClass())};

	Downloader->AddToRoot();

	Downloader->OnSingleCastDownloadProgress = OnProgress;
	Downloader->OnSingleCastDownloadComplete = OnComplete;

	Downloader->DownloadFileToStorage(URL, SavePath, Timeout, ContentType);

	return Downloader;
}

void UFileToStorageDownloader::DownloadFileToStorage(const FString& URL, const FString& SavePath, float Timeout, const FString& ContentType)
{
	if (URL.IsEmpty())
	{
		UE_LOG(LogRuntimeFilesDownloader, Error, TEXT("You have not provided an URL to download the file"));
		BroadcastResult(EDownloadToStorageResult::InvalidURL);
		return;
	}

	if (SavePath.IsEmpty())
	{
		UE_LOG(LogRuntimeFilesDownloader, Error, TEXT("You have not provided a path to save the file"));
		BroadcastResult(EDownloadToStorageResult::InvalidSavePath);
		return;
	}

	if (Timeout < 0) Timeout = 0;

	FileSavePath = SavePath;

#if ENGINE_MAJOR_VERSION >= 5 || ENGINE_MINOR_VERSION >= 26
	const TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest{FHttpModule::Get().CreateRequest()};
#else
	const TSharedRef<IHttpRequest> HttpRequest {FHttpModule::Get().CreateRequest()};
#endif

	HttpRequest->SetVerb("GET");
	HttpRequest->SetURL(URL);

#if ENGINE_MAJOR_VERSION >= 5 || ENGINE_MINOR_VERSION >= 26
	HttpRequest->SetTimeout(Timeout);
#else
	UE_LOG(LogRuntimeFilesDownloader, Warning, TEXT("The functionality to set Timeout has been available since version 4.26. Please update the engine version for this support"));
#endif

	if (!ContentType.IsEmpty())
	{
		HttpRequest->SetHeader(TEXT("Content-Type"), ContentType);
	}

	HttpRequest->OnProcessRequestComplete().BindUObject(this, &UFileToStorageDownloader::OnComplete_Internal);
	HttpRequest->OnRequestProgress().BindUObject(this, &URuntimeFilesDownloaderLibrary::OnProgress_Internal);

	/** Process the request */
	HttpRequest->ProcessRequest();

	HttpDownloadRequest = &HttpRequest.Get();
}

void UFileToStorageDownloader::BroadcastResult(EDownloadToStorageResult Result) const
{
	OnSingleCastDownloadComplete.ExecuteIfBound(Result);

	if (OnDownloadComplete.IsBound())
	{
		OnDownloadComplete.Broadcast(Result);
	}

	if (!OnSingleCastDownloadComplete.IsBound() && !OnDownloadComplete.IsBound())
	{
		UE_LOG(LogRuntimeFilesDownloader, Error, TEXT("You did not bind to a delegate to get download result"));
	}
}


void UFileToStorageDownloader::OnComplete_Internal(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	RemoveFromRoot();

	HttpDownloadRequest = nullptr;

	if (!Response.IsValid() || !EHttpResponseCodes::IsOk(Response->GetResponseCode()) || !bWasSuccessful)
	{
		UE_LOG(LogRuntimeFilesDownloader, Error, TEXT("An error occurred while downloading the file to storage"));

		if (!Response.IsValid())
		{
			UE_LOG(LogRuntimeFilesDownloader, Error, TEXT("Response is not valid"));
		}

		if (!EHttpResponseCodes::IsOk(Response->GetResponseCode()))
		{
			UE_LOG(LogRuntimeFilesDownloader, Error, TEXT("Status code is not Ok"));
		}

		if (!bWasSuccessful)
		{
			UE_LOG(LogRuntimeFilesDownloader, Error, TEXT("Download failed"));
		}

		BroadcastResult(EDownloadToStorageResult::DownloadFailed);

		return;
	}

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	/** Create save directory if not existent */
	{
		FString Path, Filename, Extension;
		FPaths::Split(FileSavePath, Path, Filename, Extension);
		if (!PlatformFile.DirectoryExists(*Path))
		{
			if (!PlatformFile.CreateDirectoryTree(*Path))
			{
				UE_LOG(LogRuntimeFilesDownloader, Error, TEXT("Unable to create directory to save downloaded file"));
				BroadcastResult(EDownloadToStorageResult::DirectoryCreationFailed);
				return;
			}
		}
	}

	/** Delete the file if it already exists */
	if (!FileSavePath.IsEmpty() && FPaths::FileExists(*FileSavePath))
	{
		IFileManager& FileManager = IFileManager::Get();
		FileManager.Delete(*FileSavePath);
	}

	/** Open / Create the file */
	IFileHandle* FileHandle = PlatformFile.OpenWrite(*FileSavePath);
	if (FileHandle)
	{
		/** Write the file */
		FileHandle->Write(Response->GetContent().GetData(), Response->GetContentLength());

		/** Close the file */
		delete FileHandle;

		Response.Reset();

		BroadcastResult(EDownloadToStorageResult::SuccessDownloading);
	}
	else
	{
		UE_LOG(LogRuntimeFilesDownloader, Error, TEXT("Something went wrong while saving the file '%s'"), *FileSavePath);
		BroadcastResult(EDownloadToStorageResult::SaveFailed);
	}
}
