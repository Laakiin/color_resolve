# color_resolve

**Résolution des couleurs pour Rubik's Cube**

Ce projet permet d'analyser une image d'un Rubik's Cube et d'identifier les couleurs de chaque face. Pour que le traitement fonctionne correctement, l'image doit être recadrée selon les dimensions attendues.

---

## Prérequis

- Une image claire et nette d'un Rubik's Cube.
- L'outil [`ImageMagick`](https://imagemagick.org/) (pour le recadrage de l'image).

---

## Utilisation

### 1. Recadrer l'image
Avant de lancer l'analyse, assurez-vous que l'image est correctement recadrée. Utilisez la commande suivante avec `ImageMagick` :

```bash
convert src.jpg -crop 327x327+150+80 out.jpg
```
- **`src.jpg`** : Image source du Rubik's Cube.
- **`out.jpg`** : Image recadrée (327x327 pixels), prête pour l'analyse.

⚠️ **Important** : Si l'image n'est pas recadrée, elle ne correspondra pas au masque utilisé par le programme, et le traitement échouera.


