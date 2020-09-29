// BlobQuickstartV12.cpp

//<Snippet_Includes>
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <stdlib.h>
#include "azure\storage\blobs\blob.hpp"
//</Snippet_Includes>

int main()
{
    std::cout << "Azure Blob storage v12 - C++ quickstart sample" << std::endl;

    //<Snippet_ConnectionString>
    // Retrieve the connection string for use with the application. The storage
    // connection string is stored in an environment variable on the machine
    // running the application called AZURE_STORAGE_CONNECTION_STRING.
    const char* connectionString = std::getenv("AZURE_STORAGE_CONNECTION_STRING");
    //</Snippet_ConnectionString>

    using namespace Azure::Storage::Blobs;

    std::string containerName = "myblobcontainer";
    std::string blobName = "blob.txt";
    std::string blobContent = "Hello Azure!";

    try
    {
        //<Snippet_CreateContainer>
        // Initialize a new instance of BlobContainerClient
        BlobContainerClient containerClient =
            BlobContainerClient::CreateFromConnectionString(connectionString, containerName);

        try
        {
            // Create the container. This will throw an exception if the container already exists.
            containerClient.Create();
        }
        catch (std::runtime_error& e)
        {
            std::cout << "Error: " << e.what() << std::endl;
        }
        //</Snippet_CreateContainer>

        //<Snippet_UploadBlob>
        // Create the block blob client
        BlockBlobClient blobClient = containerClient.GetBlockBlobClient(blobName);

        // Upload the blob
        std::cout << "Uploading blob: " << blobName << std::endl;
        blobClient.UploadFrom(reinterpret_cast<const uint8_t*>(blobContent.data()), blobContent.size());
        //</Snippet_UploadBlob>

        //<Snippet_ListBlobs>
        std::cout << "Listing blobs..." << std::endl;

        auto response = containerClient.ListBlobsFlatSegment();

        ListBlobsFlatSegmentResult result = response.ExtractValue();

        for (BlobItem blobItem : result.Items)
        {
            std::cout << "Blob name: " << blobItem.Name.data() << std::endl;
        }
        //</Snippet_ListBlobs>

        //<Snippet_DownloadBlob>
        blobClient.DownloadTo(reinterpret_cast<uint8_t*>(&blobContent[0]), blobContent.size());

        std::cout << blobContent << std::endl;
        //</Snippet_DownloadBlob>

        //<Snippet_DeleteBlob>
        blobClient.Delete();
        //</Snippet_DeleteBlob>

        //<Snippet_DeleteContainer>
        containerClient.Delete();
        //</Snippet_DeleteContainer>

    }
    catch (std::runtime_error& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }
    
}
