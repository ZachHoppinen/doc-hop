def parse_rs2_xml(xml_filepath):
    tree = ET.parse(xml_filepath)
    root = tree.getroot()

    parsed = {}
    parsed['filename'] = Path(xml_filepath).parent.stem
    parsed["product_id"] = root[0].text
    parsed["beam_mode"] = root[2][6].text
    parsed["time"] = pd.to_datetime(root[2][7].text)
    parsed["pols"] = root[2][8][2].text
    parsed["center_freq"] = float(root[2][8][7].text)
    parsed["sigma_naughts_db"] = root[2][8][21][3].text
    parsed["inc_near"] = float(root[3][1][29].text)
    parsed["inc_far"] = float(root[3][1][30].text)
    parsed["data_type"] = root[4][2][0].text
    parsed["bits_per_sample_real"] = int(root[4][2][1].text)
    parsed["bits_per_sample_complex"] = int(root[4][2][2].text)
    parsed["samples_per_line"] = int(root[4][2][3].text)
    parsed["lines"] = int(root[4][2][4].text)
    parsed["pixel_spacing_m"] = float(root[4][2][5].text)
    parsed["line_spacing_m"] = float(root[4][2][6].text)
    parsed["zero_zero_location"] = {'line/y': {int(float(root[4][3][0][0][0][0].text)): float(root[4][3][0][0][1][0].text)}, 'pixel/x': {int(float(root[4][3][0][0][0][1].text)): float(root[4][3][0][0][1][1].text)}, 'units' : 'lat/long degree'}

    grid= []
    for i, tp in enumerate(root[4][3][0]):
        tp_dic = {}
        tp_dic['y'] = {int(float(tp[0][0].text)): float(tp[1][0].text)}
        tp_dic['x'] = {int(float(tp[0][1].text)): float(tp[1][1].text)}
        grid.append(tp_dic)       
    parsed["grid"] = grid

    parsed["ellipsoid"] = {'datum_shift': root[4][3][2][3].text, 'ellipsoid_name': root[4][3][2][0].text, 'semiMajorAxis': root[4][3][2][1].text, 'semiMinorAxis': root[4][3][2][2].text}

    return parsed
