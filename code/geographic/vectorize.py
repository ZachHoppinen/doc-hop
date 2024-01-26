from rasterio import features
def vectorize_valid(fp):
    """
    Vectorize geotiff to valid pixels. Will only keep largest subset of pixels.
    """
    img = rxa.open_rasterio(fp).squeeze('band')
    img = ~img.isnull()
    img = img.astype('uint8')
    mask = img == 1
    return Polygon(list((features.shapes(img, mask = mask)))[0][0]['coordinates'][0])
