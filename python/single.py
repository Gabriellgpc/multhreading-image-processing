import os
import cv2                           # pip install opencv-python
from glob import glob

from tqdm import tqdm

input_folder  = '../images'
output_folder = './output'

def convert_to_grayscale(image_path, output_folder):
    img = cv2.imread(image_path)
    gray_img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    output_path = os.path.join(output_folder, os.path.basename(image_path))
    cv2.imwrite(output_path, gray_img)

if __name__ == "__main__":
   # get a list of abs path for all .jpg files whitin input_folder
    image_files = glob(f"{input_folder}/*.jpg")
    os.makedirs(output_folder, exist_ok=True)

    # Parallel processing using Joblib
    # Parallel(n_jobs=-1)(delayed(convert_to_grayscale)(image, output_folder) for image in image_files)
    for path in tqdm(image_files):
        convert_to_grayscale(path, output_folder)