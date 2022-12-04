#ifndef _RII_H_
#define _RII_H_
#include <map>

template <class PreImage, class Image>
class R11 {
 private:
   std::map<PreImage, Image> PreImagenes;
   std::map<Image, PreImage> Imagenes;
 public:
   R11() = default;
   ~R11() = default;
   void AgregarRelacion(PreImage preimagen, Image imagen) {
     PreImagenes.insert({preimagen, imagen});
     Imagenes.insert({imagen, preimagen});
   }

   Image Img(PreImage preimagen) {
     return PreImagenes[preimagen];
   }

   PreImage PreImg(Image imagen) {
     return Imagenes[imagen];
   }
};

#endif