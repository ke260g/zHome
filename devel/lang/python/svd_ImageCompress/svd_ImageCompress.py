import numpy as np
import matplotlib.pyplot as plt
import scipy.ndimage
import scipy.misc

def rebuild_img(U, S, V, step):
    nimg = np.zeros((U.shape[0], V.shape[0]))
    step = int(step)

    for k in range(step):
        Uk = np.mat(U[:, k].reshape(U.shape[0], 1))
        Sk = np.mat(S[k])
        Vk = np.mat(V[k].reshape(1, V.shape[0]))
        nimg += Uk * Sk * Vk

    print('step: %s'%(step))
    nimg[nimg < 0] = 0
    nimg[nimg > 255] = 255
    return np.round(nimg).astype("uint8")

img = scipy.misc.imread('image.jpg', flatten=True)

U, S, V = np.linalg.svd(img)
step = len(S) / 10

for step in np.arange(step, len(S), step):
    new_img = rebuild_img(U, S, V, step)
    plt.imshow(img); plt.show()
