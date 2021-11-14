#include <iostream>
#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/Bucket.h>
#include <aws/s3/model/ListObjectsRequest.h>


bool ListBuckets(const Aws::String& bucketName,
                 const Aws::String& region) {
    Aws::Client::ClientConfiguration config;

    if (!region.empty()) {
        config.region = region;
    }
    Aws::S3::S3Client s3_client(config);

    Aws::S3::Model::ListObjectsRequest request;
    request.WithBucket(bucketName);
    auto outcome = s3_client.ListObjects(request);
    if (outcome.IsSuccess()) {
        std::cout << "Objects in bucket '" << bucketName << "':"
             << std::endl << std::endl;

        Aws::Vector<Aws::S3::Model::Object> objects = outcome.GetResult().GetContents();

        for (Aws::S3::Model::Object& object : objects)
        {
            std::cout << object.GetKey() << std::endl;
        }

        return true;
    }
    else
    {
        std::cout << "Error: ListObjects: " <<
                  outcome.GetError().GetMessage() << std::endl;

        return false;
    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    Aws::SDKOptions options;
    Aws::InitAPI(options);
    {
        const Aws::String bucket_name = "abcbucket";

        Aws::String region = "ap-east-1";

        if (!ListBuckets(bucket_name, region))
        {
            return 1;
        }
    }
    Aws::ShutdownAPI(options);

    return 0;
}
