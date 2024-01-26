from rasterio import features
def vectorize_valid(fp):
    img = rxa.open_rasterio(fp).squeeze('band')
    img = ~img.isnull()
    img = img.astype('uint8')
    mask = img == 1
    coords = list((features.shapes(img, mask = mask)))[0][0]['coordinates'][0]
    xy_coords = [(img.x[int(x)].values.ravel()[0], img.y[int(y)].values.ravel()[0]) for x, y in coords]
    return Polygon(xy_coords)
