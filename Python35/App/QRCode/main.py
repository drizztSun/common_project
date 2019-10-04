import segno

# Usage
# Command line
# The command line script prints the QR Code to the terminal:

# $ segno "Comfortably Numb"
# To serialize the QR Code, use the “output” argument:

# $ segno -o=raincoat.svg "Famous Blue Raincoat"
# $ segno --scale=10 --color=darkblue --border=0 --output=fire.svg "Who by Fire"
# $ segno --scale=10 --background=transparent --output=miracle.png "Waiting for the Miracle

def output_qr_hdl(qr):

    print("version: ", qr.version)
    print("is_macro: ", qr.is_micro)
    print("error: ", qr.error)
    print("designor: ", qr.designator)
    print("default_borader_size: ", qr.default_border_size)
    print("mode: ", qr.mode)



def create_qrcode(content):

    return segno.make(content)

def create_micro_qrcode(content):

    qr = segno.make_micro(content)

    return qr

def main():

    qr = create_qrcode("SYX segno testing case")

    output_qr_hdl(qr)

    # qr.save('up-jumped-the-devil.png') # save as png
    # qr.save('up-jumped-the-devil-2.png', scale=10) # Scaling factor 10
    # qr.save('up-jumped-the-devil-3.png', background=None) # Transparent backgournd
    # qr.save('up-jumped-the-devil.pdf', scale=10)  # Save as PDF
    # qr.save('up-jumped-the-devil.svg', scale=10, color='darkblue') # SVG drawing the dark modules in "dark blue"

    width, height = qr.symbol_size()
    res = []
    # Scaling factor 2, default border
    for row in qr.matrix_iter(scale=2):
        res.append([co == 0x1 for co in row])

    print("width * 2 == len(res[0]) :", width * 2 == len(res[0]))
    print("height * 2 == len(res) : ", height * 2 == len(res))


if __name__ == '__main__':

    main()
