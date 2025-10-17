Adapted from Daniel Shifmann image/video to ascii originally in p5.js
uses stb_image.h and stb_image_resize.h

to be used in [ft_ascii](https://github.com/carlocattano/ft_ascii)

Written in c with stb headers only library.

### Usage:

Build the tool

```
git clone https://github.com/carlocattano/img2txt
cd img2txt
make
```

Run

```
./img2txt <image.(png/jpg)> [-s size] [-c 256]
```

You can also pipe an image into the program:

```
cat image.jpg | ./img2txt
wget -O - <url_to_image> | ./img2txt
```

_img2txt_ picture.jpg, will default to your current terminal size

<img width="1907" height="991" alt="image" src="https://github.com/user-attachments/assets/7dada524-e5c1-41d3-a1c9-9366d854dbfb" />

```

### Image:

zebra.jpg [Author](https://www.publicdomainpictures.net/en/view-image.php?image=455680&picture=zebra)
License: CC0 Public Domain
