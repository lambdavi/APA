#
# Author: Davide Buoso
# REQUIRED: youtube_dl
#

import youtube_dl
params = {
    'format': 'best',
    'postprocessors': [{
        'key': 'FFmpegExtractAudio',
        'preferredcodec': 'mp4',
        'preferredquality': '192',
    }],
}
if __name__ == "__main__":
    url = [input('Enter the link:')]
    with youtube_dl.YoutubeDL(params) as ydl:
        ydl.download(url)


