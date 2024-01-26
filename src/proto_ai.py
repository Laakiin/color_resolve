# This is a sample Python script.

# Press Maj+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.
import math

class color_rgb_t:
    def __init__(self, r, g, b, color_name):
        self.r = r
        self.g = g
        self.b = b
        self.color_name = color_name

class color_hsl_t:
    def __init__(self, h, s, l, color_name):
        self.h = h
        self.s = s
        self.l = l
        self.color_name = color_name

class colorStat_t:
    def __init__(self,color_name,color_component,esperence,variance,Pcolor):
        self.color_name = color_name
        self.color_component = color_component
        self.esperence = esperence
        self.variance = variance
        self.Pcolor = Pcolor


#function that convert rgb to hsl with a color_rgb_t object in parameter and return a color_hsl_t object
def rgb_to_hsl(color_rgb):
    r = color_rgb.r / 255
    g = color_rgb.g / 255
    b = color_rgb.b / 255

    cmax = max(r, g, b)
    cmin = min(r, g, b)
    delta = cmax - cmin

    if delta == 0:
        h = 0
    elif cmax == r:
        h = 60 * (((g - b) / delta) % 6)
    elif cmax == g:
        h = 60 * (((b - r) / delta) + 2)
    elif cmax == b:
        h = 60 * (((r - g) / delta) + 4)

    if cmax == 0:
        s = 0
    else:
        s = (delta / cmax) * 255

    l = ((cmax + cmin) / 2) * 255

    return color_hsl_t(int(h), int(s), int(l), color_rgb.color_name)
def sortByColorName(colors):
    JAUNES = []
    BLEUS = []
    ROUGES = []
    VERTS = []
    BLANCS = []
    ORANGES = []
    for i in range(len(colors)):
        if colors[i].color_name == "JAUNE":
            JAUNES.append(colors[i])
        elif colors[i].color_name == "BLEU":
            BLEUS.append(colors[i])
        elif colors[i].color_name == "ROUGE":
            ROUGES.append(colors[i])
        elif colors[i].color_name == "VERT":
            VERTS.append(colors[i])
        elif colors[i].color_name == "BLANC":
            BLANCS.append(colors[i])
        elif colors[i].color_name == "ORANGE":
            ORANGES.append(colors[i])

    return JAUNES , BLEUS , ROUGES , VERTS , BLANCS , ORANGES

def esperence_color_rgb(colors):
    esperence_r = 0
    esperence_g = 0
    esperence_b = 0
    for i in range(len(colors)):
        esperence_r += colors[i].r
        esperence_g += colors[i].g
        esperence_b += colors[i].b
    return esperence_r/len(colors), esperence_g/len(colors), esperence_b/len(colors)

def variance_color_rgb(colors):
    variance_r = 0
    variance_g = 0
    variance_b = 0
    esperence_r,esperence_g,esperence_b = esperence_color_rgb(colors)
    for i in range(len(colors)):
        variance_r += (colors[i].r - esperence_r)**2
        variance_g += (colors[i].g - esperence_g)**2
        variance_b += (colors[i].b - esperence_b)**2
    return variance_r / len(colors), variance_g / len(colors), variance_b / len(colors)

def esperence_color_hsl(colors):
    esperence_h = 0
    esperence_s = 0
    esperence_l = 0
    for i in range(len(colors)):
        esperence_h += colors[i].h
        esperence_s += colors[i].s
        esperence_l += colors[i].l
    return esperence_h / len(colors), esperence_s / len(colors), esperence_l / len(colors)

def variance_color_hsl(colors):
    variance_h = 0
    variance_s = 0
    variance_l = 0
    esperence_h, esperence_s, esperence_l = esperence_color_hsl(colors)
    for i in range(len(colors)):
        variance_h += (colors[i].h - esperence_h) ** 2
        variance_s += (colors[i].s - esperence_s) ** 2
        variance_l += (colors[i].l - esperence_l) ** 2
    return variance_h / len(colors), variance_s / len(colors), variance_l / len(colors)

def calculateColorStats_rgb(colors):
    JAUNES, BLEUS, ROUGES, VERTS, BLANCS, ORANGES = sortByColorName(colors)
    lenJAUNES = len(JAUNES)
    lenBLEUS = len(BLEUS)
    lenROUGES = len(ROUGES)
    lenVERTS = len(VERTS)
    lenBLANCS = len(BLANCS)
    lenORANGES = len(ORANGES)
    lenTOTAL= len(colors)

    colorStats = []
    esperence_r, esperence_g, esperence_b = esperence_color_rgb(JAUNES)
    variance_r, variance_g, variance_b = variance_color_rgb(JAUNES)
    colorStats.append(colorStat_t("JAUNE","r",esperence_r,variance_r,lenJAUNES/lenTOTAL))
    colorStats.append(colorStat_t("JAUNE","g",esperence_g,variance_g,lenJAUNES/lenTOTAL))
    colorStats.append(colorStat_t("JAUNE","b",esperence_b,variance_b,lenJAUNES/lenTOTAL))
    esperence_r, esperence_g, esperence_b = esperence_color_rgb(BLEUS)
    variance_r, variance_g, variance_b = variance_color_rgb(BLEUS)
    colorStats.append(colorStat_t("BLEU","r",esperence_r,variance_r,lenBLEUS/lenTOTAL))
    colorStats.append(colorStat_t("BLEU","g",esperence_g,variance_g,lenBLEUS/lenTOTAL))
    colorStats.append(colorStat_t("BLEU","b",esperence_b,variance_b,lenBLEUS/lenTOTAL))
    esperence_r, esperence_g, esperence_b = esperence_color_rgb(ROUGES)
    variance_r, variance_g, variance_b = variance_color_rgb(ROUGES)
    colorStats.append(colorStat_t("ROUGE","r",esperence_r,variance_r,lenROUGES/lenTOTAL))
    colorStats.append(colorStat_t("ROUGE","g",esperence_g,variance_g,lenROUGES/lenTOTAL))
    colorStats.append(colorStat_t("ROUGE","b",esperence_b,variance_b,lenROUGES/lenTOTAL))
    esperence_r, esperence_g, esperence_b = esperence_color_rgb(VERTS)
    variance_r, variance_g, variance_b = variance_color_rgb(VERTS)
    colorStats.append(colorStat_t("VERT","r",esperence_r,variance_r,lenVERTS/lenTOTAL))
    colorStats.append(colorStat_t("VERT","g",esperence_g,variance_g,lenVERTS/lenTOTAL))
    colorStats.append(colorStat_t("VERT","b",esperence_b,variance_b,lenVERTS/lenTOTAL))
    esperence_r, esperence_g, esperence_b = esperence_color_rgb(BLANCS)
    variance_r, variance_g, variance_b = variance_color_rgb(BLANCS)
    colorStats.append(colorStat_t("BLANC","r",esperence_r,variance_r,lenBLANCS/lenTOTAL))
    colorStats.append(colorStat_t("BLANC","g",esperence_g,variance_g,lenBLANCS/lenTOTAL))
    colorStats.append(colorStat_t("BLANC","b",esperence_b,variance_b,lenBLANCS/lenTOTAL))
    esperence_r, esperence_g, esperence_b = esperence_color_rgb(ORANGES)
    variance_r, variance_g, variance_b = variance_color_rgb(ORANGES)
    colorStats.append(colorStat_t("ORANGE","r",esperence_r,variance_r,lenORANGES/lenTOTAL))
    colorStats.append(colorStat_t("ORANGE","g",esperence_g,variance_g,lenORANGES/lenTOTAL))
    colorStats.append(colorStat_t("ORANGE","b",esperence_b,variance_b,lenORANGES/lenTOTAL))
    return colorStats

def calculateColorStats_hsl(colors):

    hsl_colors = [rgb_to_hsl(color) for color in colors]

    JAUNES, BLEUS, ROUGES, VERTS, BLANCS, ORANGES = sortByColorName(hsl_colors)
    lenJAUNES = len(JAUNES)
    lenBLEUS = len(BLEUS)
    lenROUGES = len(ROUGES)
    lenVERTS = len(VERTS)
    lenBLANCS = len(BLANCS)
    lenORANGES = len(ORANGES)
    lenTOTAL = len(hsl_colors)

    colorStats = []

    # Pour la couleur JAUNE
    esperence_h, esperence_s, esperence_l = esperence_color_hsl(JAUNES)
    variance_h, variance_s, variance_l = variance_color_hsl(JAUNES)
    colorStats.append(colorStat_t("JAUNE", "h", esperence_h, variance_h, lenJAUNES / lenTOTAL))
    colorStats.append(colorStat_t("JAUNE", "s", esperence_s, variance_s, lenJAUNES / lenTOTAL))
    colorStats.append(colorStat_t("JAUNE", "l", esperence_l, variance_l, lenJAUNES / lenTOTAL))

    # Pour la couleur BLEU
    esperence_h, esperence_s, esperence_l = esperence_color_hsl(BLEUS)
    variance_h, variance_s, variance_l = variance_color_hsl(BLEUS)
    colorStats.append(colorStat_t("BLEU", "h", esperence_h, variance_h, lenBLEUS / lenTOTAL))
    colorStats.append(colorStat_t("BLEU", "s", esperence_s, variance_s, lenBLEUS / lenTOTAL))
    colorStats.append(colorStat_t("BLEU", "l", esperence_l, variance_l, lenBLEUS / lenTOTAL))

    # Pour la couleur ROUGE
    esperence_h, esperence_s, esperence_l = esperence_color_hsl(ROUGES)
    variance_h, variance_s, variance_l = variance_color_hsl(ROUGES)
    colorStats.append(colorStat_t("ROUGE", "h", esperence_h, variance_h, lenROUGES / lenTOTAL))
    colorStats.append(colorStat_t("ROUGE", "s", esperence_s, variance_s, lenROUGES / lenTOTAL))
    colorStats.append(colorStat_t("ROUGE", "l", esperence_l, variance_l, lenROUGES / lenTOTAL))

    # Pour la couleur VERT
    esperence_h, esperence_s, esperence_l = esperence_color_hsl(VERTS)
    variance_h, variance_s, variance_l = variance_color_hsl(VERTS)
    colorStats.append(colorStat_t("VERT", "h", esperence_h, variance_h, lenVERTS / lenTOTAL))
    colorStats.append(colorStat_t("VERT", "s", esperence_s, variance_s, lenVERTS / lenTOTAL))
    colorStats.append(colorStat_t("VERT", "l", esperence_l, variance_l, lenVERTS / lenTOTAL))

    # Pour la couleur BLANC
    esperence_h, esperence_s, esperence_l = esperence_color_hsl(BLANCS)
    variance_h, variance_s, variance_l = variance_color_hsl(BLANCS)
    colorStats.append(colorStat_t("BLANC", "h", esperence_h, variance_h, lenBLANCS / lenTOTAL))
    colorStats.append(colorStat_t("BLANC", "s", esperence_s, variance_s, lenBLANCS / lenTOTAL))
    colorStats.append(colorStat_t("BLANC", "l", esperence_l, variance_l, lenBLANCS / lenTOTAL))

    # Pour la couleur ORANGE
    esperence_h, esperence_s, esperence_l = esperence_color_hsl(ORANGES)
    variance_h, variance_s, variance_l = variance_color_hsl(ORANGES)
    colorStats.append(colorStat_t("ORANGE", "h", esperence_h, variance_h, lenORANGES / lenTOTAL))
    colorStats.append(colorStat_t("ORANGE", "s", esperence_s, variance_s, lenORANGES / lenTOTAL))
    colorStats.append(colorStat_t("ORANGE", "l", esperence_l, variance_l, lenORANGES / lenTOTAL))

    return colorStats

def gaussianDistribution(x,esperence,variance):
    return 1/(math.sqrt(2*math.pi*variance))*math.exp(-((x-esperence)**2)/(2*variance))

def NBC_rgb(x, colorStats):
    Pcolor=1/6
    P_JAUNE_r = gaussianDistribution(x.r,colorStats[0].esperence,colorStats[0].variance)
    P_JAUNE_g = gaussianDistribution(x.g,colorStats[1].esperence,colorStats[1].variance)
    P_JAUNE_b = gaussianDistribution(x.b,colorStats[2].esperence,colorStats[2].variance)
    P_JAUNE = P_JAUNE_r*P_JAUNE_g*P_JAUNE_b*colorStats[0].Pcolor
    P_BLEU_r = gaussianDistribution(x.r,colorStats[3].esperence,colorStats[3].variance)
    P_BLEU_g = gaussianDistribution(x.g,colorStats[4].esperence,colorStats[4].variance)
    P_BLEU_b = gaussianDistribution(x.b,colorStats[5].esperence,colorStats[5].variance)
    P_BLEU = P_BLEU_r*P_BLEU_g*P_BLEU_b*colorStats[3].Pcolor
    P_ROUGE_r = gaussianDistribution(x.r,colorStats[6].esperence,colorStats[6].variance)
    P_ROUGE_g = gaussianDistribution(x.g,colorStats[7].esperence,colorStats[7].variance)
    P_ROUGE_b = gaussianDistribution(x.b,colorStats[8].esperence,colorStats[8].variance)
    P_ROUGE = P_ROUGE_r*P_ROUGE_g*P_ROUGE_b*colorStats[6].Pcolor
    P_VERT_r = gaussianDistribution(x.r,colorStats[9].esperence,colorStats[9].variance)
    P_VERT_g = gaussianDistribution(x.g,colorStats[10].esperence,colorStats[10].variance)
    P_VERT_b = gaussianDistribution(x.b,colorStats[11].esperence,colorStats[11].variance)
    P_VERT = P_VERT_r*P_VERT_g*P_VERT_b*colorStats[9].Pcolor
    P_BLANC_r = gaussianDistribution(x.r,colorStats[12].esperence,colorStats[12].variance)
    P_BLANC_g = gaussianDistribution(x.g,colorStats[13].esperence,colorStats[13].variance)
    P_BLANC_b = gaussianDistribution(x.b,colorStats[14].esperence,colorStats[14].variance)
    P_BLANC = P_BLANC_r*P_BLANC_g*P_BLANC_b*colorStats[12].Pcolor
    P_ORANGE_r = gaussianDistribution(x.r,colorStats[15].esperence,colorStats[15].variance)
    P_ORANGE_g = gaussianDistribution(x.g,colorStats[16].esperence,colorStats[16].variance)
    P_ORANGE_b = gaussianDistribution(x.b,colorStats[17].esperence,colorStats[17].variance)
    P_ORANGE = P_ORANGE_r*P_ORANGE_g*P_ORANGE_b*colorStats[15].Pcolor

    evidence= P_JAUNE+P_BLEU+P_ROUGE+P_VERT+P_BLANC+P_ORANGE
    P_JAUNE = P_JAUNE/evidence
    P_BLEU = P_BLEU/evidence
    P_ROUGE = P_ROUGE/evidence
    P_VERT = P_VERT/evidence
    P_BLANC = P_BLANC/evidence
    P_ORANGE = P_ORANGE/evidence

    return P_JAUNE,P_BLEU,P_ROUGE,P_VERT,P_BLANC,P_ORANGE

def NBC_hsl(x, colorStats):
    # Convert RGB color to HSL
    x_hsl = rgb_to_hsl(x)

    P_JAUNE_h = gaussianDistribution(x_hsl.h, colorStats[0].esperence, colorStats[0].variance)
    P_JAUNE_s = gaussianDistribution(x_hsl.s, colorStats[1].esperence, colorStats[1].variance)
    P_JAUNE_l = gaussianDistribution(x_hsl.l, colorStats[2].esperence, colorStats[2].variance)
    P_JAUNE = P_JAUNE_h * P_JAUNE_s * P_JAUNE_l * colorStats[0].Pcolor
    P_BLEU_h = gaussianDistribution(x_hsl.h, colorStats[3].esperence, colorStats[3].variance)
    P_BLEU_s = gaussianDistribution(x_hsl.s, colorStats[4].esperence, colorStats[4].variance)
    P_BLEU_l = gaussianDistribution(x_hsl.l, colorStats[5].esperence, colorStats[5].variance)
    P_BLEU = P_BLEU_h * P_BLEU_s * P_BLEU_l * colorStats[3].Pcolor
    P_ROUGE_h = gaussianDistribution(x_hsl.h, colorStats[6].esperence, colorStats[6].variance)
    P_ROUGE_s = gaussianDistribution(x_hsl.s, colorStats[7].esperence, colorStats[7].variance)
    P_ROUGE_l = gaussianDistribution(x_hsl.l, colorStats[8].esperence, colorStats[8].variance)
    P_ROUGE = P_ROUGE_h * P_ROUGE_s * P_ROUGE_l * colorStats[6].Pcolor
    P_VERT_h = gaussianDistribution(x_hsl.h, colorStats[9].esperence, colorStats[9].variance)
    P_VERT_s = gaussianDistribution(x_hsl.s, colorStats[10].esperence, colorStats[10].variance)
    P_VERT_l = gaussianDistribution(x_hsl.l, colorStats[11].esperence, colorStats[11].variance)
    P_VERT = P_VERT_h * P_VERT_s * P_VERT_l * colorStats[9].Pcolor
    P_BLANC_h = gaussianDistribution(x_hsl.h, colorStats[12].esperence, colorStats[12].variance)
    P_BLANC_s = gaussianDistribution(x_hsl.s, colorStats[13].esperence, colorStats[13].variance)
    P_BLANC_l = gaussianDistribution(x_hsl.l, colorStats[14].esperence, colorStats[14].variance)
    P_BLANC = P_BLANC_h * P_BLANC_s * P_BLANC_l * colorStats[12].Pcolor
    P_ORANGE_h = gaussianDistribution(x_hsl.h, colorStats[15].esperence, colorStats[15].variance)
    P_ORANGE_s = gaussianDistribution(x_hsl.s, colorStats[16].esperence, colorStats[16].variance)
    P_ORANGE_l = gaussianDistribution(x_hsl.l, colorStats[17].esperence, colorStats[17].variance)
    P_ORANGE = P_ORANGE_h * P_ORANGE_s * P_ORANGE_l * colorStats[15].Pcolor

    evidence = P_JAUNE + P_BLEU + P_ROUGE + P_VERT + P_BLANC + P_ORANGE
    P_JAUNE = P_JAUNE / evidence
    P_BLEU = P_BLEU / evidence
    P_ROUGE = P_ROUGE / evidence
    P_VERT = P_VERT / evidence
    P_BLANC = P_BLANC / evidence
    P_ORANGE = P_ORANGE / evidence

    return P_JAUNE, P_BLEU, P_ROUGE, P_VERT, P_BLANC, P_ORANGE

#function that opens a csv file and returns a list of color_t
def openCSV(filename):
    f = open(filename, "r")
    colors = []
    line = f.readline()
    while line:
        line = line.split(',')
        colors.append(color_rgb_t(int(line[0]), int(line[1]), int(line[2]), line[3][:-1]))
        line = f.readline()
    f.close()
    return colors

#function that test if all the colors in the list are well classified and returns the number of errors
def test_rgb(colors, colorStats):
    error = 0
    success_messages = []

    for color in colors:
        P_JAUNE, P_BLEU, P_ROUGE, P_VERT, P_BLANC, P_ORANGE = NBC_rgb(color, colorStats)
        predictedColor = ""

        print(f"Test pour couleur {color.color_name} ({color.r}, {color.g}, {color.b}):")
        print("Probabilités :")
        print(f"JAUNE : {P_JAUNE:.6f}")
        print(f"BLEU : {P_BLEU:.6f}")
        print(f"ROUGE : {P_ROUGE:.6f}")
        print(f"VERT : {P_VERT:.6f}")
        print(f"BLANC : {P_BLANC:.6f}")
        print(f"ORANGE : {P_ORANGE:.6f}")

        # Trouver la couleur prédite
        if P_JAUNE > max(P_BLEU, P_ROUGE, P_VERT, P_BLANC, P_ORANGE):
            predictedColor = "JAUNE"
        elif P_BLEU > max(P_JAUNE, P_ROUGE, P_VERT, P_BLANC, P_ORANGE):
            predictedColor = "BLEU"
        elif P_ROUGE > max(P_JAUNE, P_BLEU, P_VERT, P_BLANC, P_ORANGE):
            predictedColor = "ROUGE"
        elif P_VERT > max(P_JAUNE, P_BLEU, P_ROUGE, P_BLANC, P_ORANGE):
            predictedColor = "VERT"
        elif P_BLANC > max(P_JAUNE, P_BLEU, P_ROUGE, P_VERT, P_ORANGE):
            predictedColor = "BLANC"
        elif P_ORANGE > max(P_JAUNE, P_BLEU, P_ROUGE, P_VERT, P_BLANC):
            predictedColor = "ORANGE"

        if predictedColor != color.color_name:
            error += 1
            print(f"Erreur : couleur prédite = {predictedColor}, couleur réelle = {color.color_name}")
        else:
            success_messages.append(f"{color.r},{color.g},{color.b},{color.color_name}")

        print()

    # Écrire les réussites dans un fichier 'success.csv'
    with open('success.csv', 'w') as file:
        file.write("Réussi\n")
        for success_message in success_messages:
            file.write(success_message + "\n")

    print(f"Nombre d'erreurs : {error}")

def test_hsl(colors, colorStats):
    error = 0
    success_messages = []

    for color in colors:
        P_JAUNE, P_BLEU, P_ROUGE, P_VERT, P_BLANC, P_ORANGE = NBC_hsl(color, colorStats)
        predictedColor = ""

        color_hsl = rgb_to_hsl(color)
        print(f"Test pour couleur {color.color_name} ({color_hsl.h}, {color_hsl.s}, {color_hsl.l}):")
        print("Probabilités :")
        print(f"JAUNE : {P_JAUNE:.6f}")
        print(f"BLEU : {P_BLEU:.6f}")
        print(f"ROUGE : {P_ROUGE:.6f}")
        print(f"VERT : {P_VERT:.6f}")
        print(f"BLANC : {P_BLANC:.6f}")
        print(f"ORANGE : {P_ORANGE:.6f}")

        # Trouver la couleur prédite
        if P_JAUNE > max(P_BLEU, P_ROUGE, P_VERT, P_BLANC, P_ORANGE):
            predictedColor = "JAUNE"
        elif P_BLEU > max(P_JAUNE, P_ROUGE, P_VERT, P_BLANC, P_ORANGE):
            predictedColor = "BLEU"
        elif P_ROUGE > max(P_JAUNE, P_BLEU, P_VERT, P_BLANC, P_ORANGE):
            predictedColor = "ROUGE"
        elif P_VERT > max(P_JAUNE, P_BLEU, P_ROUGE, P_BLANC, P_ORANGE):
            predictedColor = "VERT"
        elif P_BLANC > max(P_JAUNE, P_BLEU, P_ROUGE, P_VERT, P_ORANGE):
            predictedColor = "BLANC"
        elif P_ORANGE > max(P_JAUNE, P_BLEU, P_ROUGE, P_VERT, P_BLANC):
            predictedColor = "ORANGE"

        if predictedColor != color.color_name:
            error += 1
            print(f"Erreur : couleur prédite = {predictedColor}, couleur réelle = {color.color_name}")
        else:
            success_messages.append(f"{color_hsl.h},{color_hsl.s},{color_hsl.l},{color_hsl.color_name}")

        print()

    # Écrire les réussites dans un fichier 'success.csv'
    with open('success_hsl.csv', 'w') as file:
        file.write("Réussi\n")
        for success_message in success_messages:
            file.write(success_message + "\n")

    print(f"Nombre d'erreurs : {error}")

def main():
    # RGB Version
    base_rgb = openCSV("COLORS.csv")
    colorStats_rgb = calculateColorStats_rgb(base_rgb)
    sample_rgb = openCSV("sample.csv")

    print("Testing RGB:")
    test_rgb(sample_rgb, colorStats_rgb)

    print("#" * 50)

    # HSL Version
    base_hsl = openCSV("COLORS.csv")
    colorStats_hsl = calculateColorStats_hsl(base_hsl)
    sample_hsl = openCSV("sample.csv")

    print("\nTesting HSL:")
    test_hsl(sample_hsl, colorStats_hsl)

if __name__ == '__main__':
    main()