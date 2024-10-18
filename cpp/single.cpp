#include <opencv2/opencv.hpp>
#include <filesystem>
#include <string>

void convert_to_grayscale(const std::string& input_path, const std::string& output_folder)
{
    cv::Mat img = cv::imread(input_path);
    cv::Mat gray_img;
    cv::cvtColor(img, gray_img, cv::COLOR_BGR2GRAY);
    std::string output_path = output_folder + "/" + std::filesystem::path(input_path).filename().string();
    cv::imwrite(output_path, gray_img);
}

// Function to display a progress bar
void show_progress_bar(size_t current, size_t total, size_t bar_width = 50) {
    float progress = static_cast<float>(current) / total;
    size_t pos = static_cast<size_t>(bar_width * progress);

    std::cout << "[";
    for (size_t i = 0; i < bar_width; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << int(progress * 100.0) << "%\r"; // Print percentage and return to start of line
    std::cout.flush();
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
    // #pragma omp parallel for
    for (size_t i = 0; i < image_files.size(); ++i)
    {
        convert_to_grayscale(image_files[i], output_folder);
        show_progress_bar(i, image_files.size());
    }

    return 0;
}