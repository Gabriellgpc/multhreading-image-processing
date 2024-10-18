#include <string>
#include <atomic>
#include <thread>
#include <filesystem>
#include <chrono>

#include <opencv2/opencv.hpp>


void convert_to_grayscale(const std::string& input_path, const std::string& output_folder)
{
    cv::Mat img = cv::imread(input_path);
    cv::Mat gray_img;
    cv::cvtColor(img, gray_img, cv::COLOR_BGR2GRAY);
    std::string output_path = output_folder + "/" + std::filesystem::path(input_path).filename().string();
    cv::imwrite(output_path, gray_img);
}

int main(int argc, char** argv)
{
    typedef std::filesystem::path Path;
    namespace fs = std::filesystem;

    if(argc < 3)
    {
        std::cout << "Usage: " << argv[0] << " <images-folder> <output-folder>" << std::endl;
        return 1;
    }

    Path input_folder {argv[1]};
    Path output_folder{argv[2]};

    // Print inputs
    std::cout << "Input folder: " << input_folder << std::endl;
    std::cout << "Output folder: "<< output_folder << std::endl;

    //check if input folder exists
    if(!fs::exists(input_folder))
    {
        std::cerr << "Input folder does not exist: " << input_folder << std::endl;
        return 1;
    }

    //make output dir if it doesn't exist
    if(!std::filesystem::exists(output_folder))
        std::filesystem::create_directory( output_folder );

    // list all JPG images in input_folder
    std::vector<std::string> image_files;
    for (const auto& entry : fs::directory_iterator(input_folder))
    {
        image_files.emplace_back(entry.path().string());
    }

    // Parallel processing using OpenMP
    size_t total_files = image_files.size();

    // Each thread processes images
    #pragma omp parallel for
    for (size_t i = 0; i < total_files; ++i)
    {
        convert_to_grayscale(image_files[i], output_folder);
    }

    return 0;
}