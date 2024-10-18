# pip install pexel-downloader
from pexel_downloader import PexelDownloader

if __name__ == '__main__':
    downloader = PexelDownloader(api_key="YOUR-PEXELS-API-KEY")
    downloader.download_images(query='space',
                               num_images=1000,
                               save_directory='../images',
                               size='original')