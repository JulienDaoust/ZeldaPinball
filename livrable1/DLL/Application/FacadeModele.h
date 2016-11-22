//////////////////////////////////////////////////////////////////////////////
/// @file FacadeModele.h
/// @author DGI
/// @date 2005-06-15
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __APPLICATION_FACADEMODELE_H__
#define __APPLICATION_FACADEMODELE_H__

#include <windows.h>
#include <string>
#include <vector>
#include "GL/glew.h"
#include "glm/glm.hpp"
#include "../Arbre/Visiteurs/VisiteurTranslation.h"
#include "../Arbre/Visiteurs/VisiteurLireXML.h"
#include "../Arbre/Visiteurs/VisiteurEcrireXML.h"
#include "../Arbre/Visiteurs/VisiteurMouvement.h"
#include "../Arbre/Visiteurs/VisiteurScale.h"

class NoeudAbstrait;
class ArbreRenduINF2990;

namespace vue {
   class Vue;
}


///////////////////////////////////////////////////////////////////////////
/// @class FacadeModele
/// @brief Classe qui constitue une interface (une façade) sur l'ensemble
///        du modèle et des classes qui le composent.
///
/// @author Martin Bisson
/// @date 2007-02-20
///////////////////////////////////////////////////////////////////////////
class FacadeModele
{
public:
   /// Obtient l'instance unique de la classe.
   static FacadeModele* obtenirInstance();
   /// Libère l'instance unique de la classe.
   static void libererInstance();

   /// Crée un contexte OpenGL et initialise celui-ci.
   void initialiserOpenGL(HWND hWnd);
   /// Charge la configuration à partir d'un fichier XML.
   void chargerConfiguration() const;
   /// Enregistre la configuration courante dans un fichier XML.
   void enregistrerConfiguration() const;
   /// Libère le contexte OpenGL.
   void libererOpenGL();
   /// Affiche le contenu du modèle.
   void afficher() const;
   /// Affiche la base du contenu du modèle.
   void afficherBase() const;
 
   /// Retourne la vue courante.
   inline vue::Vue* obtenirVue();
   /// Retourne l'arbre de rendu.
   inline const ArbreRenduINF2990* obtenirArbreRenduINF2990() const;
   /// Retourne l'arbre de rendu.
   inline ArbreRenduINF2990* obtenirArbreRenduINF2990();
   /// ajoute un noeud à l'arbre de rendu
   void ajouterNoeud(std::string nom, glm::dvec3& point);
   /// ajoute un noeud mur à l'arbre de rendu
   void ajouterNoeudMur(glm::dvec3& point1, glm::dvec3& point2);
   /// ajoute deux noeuds portail à l'arbre de rendu
   void ajouterNoeudPortail(glm::dvec3& point1, glm::dvec3& point2);
   /// selection par clique
   void selectionSimple(glm::dvec3 point);
   /// selection par rectangle élastique
   void selectionMultiple(glm::dvec3 min, glm::dvec3 max);
   /// translation des objets sélectionnées
   void translation(glm::dvec3 point);
   /// translation de l'écran par la souris
   void translationSouris(glm::dvec3 point);
   /// mise a echellemanuelle
   void miseEchelle(double scale);
   /// rotation des objets sélectionnées
   void rotation(double angle);
   /// duplication des objets selectionner
   void duplication(glm::dvec3 point);
   /// duplication des objets selectionner
   void exitDuplication();
   /// retourne le centrer d'un groupede noeuds
   glm::dvec3 obtenirPointCentral(std::vector<NoeudAbstrait*> noeudSelectionnes);
   /// validation de deplacement
   void validateMouvement();
   /// relache les Visiteurs
   void releaseVisiteurs();
   /// Réinitialise la scène.
   void reinitialiser();
   /// Permet la mise à l'échelle des objets de la scène
   void scale(glm::dvec3 point);
   /// Permet de supprimer les objets selectionnés
   void supprimer();
   /// Permet d'obtenir les points pour passer a la prochaine campagne
   int obtenirPointsCampagne();
   /// Permet d'obtenir les points pour avoir une bille gratuite
   int obtenirPointsBille();
   /// Permet d'obtenir la difficulté
   int obtenirDifficulté();
   /// Permet d'assigner les points pour passer a la prochaine campagne
   void assignerPointsCampagne(int points);
   /// Permet d'assigner les points pour avoir une bille gratuite
   void assignerPointsBille(int points);
   /// Permet d'assigner la difficulte
   void assignerDifficulte(int points);

   /// Anime la scène.
   void animer(float temps);

   /// XML /////////////////////////////////////////////

   /// verifier la présence des objets nécessaires
   bool sauvegardePossible();

   /// gère la sauvegarde de la zone de jeu en fichier XML
   bool sauvegardeArbreXML(std::string nomFichier);

   /// lire le XML
   bool lectureXML(char* nomFichier);


   ///////////////////////////////////////////////////////
private:
   /// Constructeur par défaut.
   FacadeModele() = default;
   /// Destructeur.
   ~FacadeModele();
   /// Constructeur copie désactivé.
   FacadeModele(const FacadeModele&) = delete;
   /// Opérateur d'assignation désactivé.
   FacadeModele& operator =(const FacadeModele&) = delete;
   /// renverse le mouvement sur les objets selectionnés
   void revertMouvement();

   /// Points nécessaires pour passer a la campagne suivante
   int pointsCampagne = 1000;

   /// Points nécessaires pour obtenir une bille gratuite
   int pointsBille = 200;

   /// Niveau de difficulté
   int difficulte;

   /// Nom du fichier XML dans lequel doit se trouver la configuration.
   static const std::string FICHIER_CONFIGURATION;

   /// Pointeur vers l'instance unique de la classe.
   static FacadeModele* instance_;

   /// Pointeur vers le visiteur de translation
   static VisiteurTranslation* visiteurTranslation;
   static VisiteurMouvement* visiteurMouvement_;

   /// Pointeur vers le visiteur de lire XML
   static VisiteurLireXML* visiteurLireXML;
   /// Pointeur vers le visiteur pour écrire XML
   static VisiteurEcrireXML* visiteurEcrireXML;

   /// Poignée ("handle") vers la fenêtre où l'affichage se fait.
   HWND  hWnd_{ nullptr };
   /// Poignée ("handle") vers le contexte OpenGL.
   HGLRC hGLRC_{ nullptr };
   /// Poignée ("handle") vers le "device context".
   HDC   hDC_{ nullptr };

   /// Vue courante de la scène.
   vue::Vue* vue_{ nullptr };
   /// Arbre de rendu contenant les différents objets de la scène.
   ArbreRenduINF2990* arbre_{ nullptr };

};



////////////////////////////////////////////////////////////////////////
///
/// @fn inline vue::Vue* FacadeModele::obtenirVue()
///
/// Cette fonction retourne la vue qui est présentement utilisée pour
/// voir la scène.
///
/// @return La vue courante.
///
////////////////////////////////////////////////////////////////////////
inline vue::Vue* FacadeModele::obtenirVue()
{
   return vue_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline int FacadeModele::obtenirPointsCampagne()
///
/// Cette fonction retourne le nombre de points requis pour passer a la campagne suivante
///
/// @return le nombre de points requis pour passer a la campagne suivante
///
////////////////////////////////////////////////////////////////////////
inline int FacadeModele::obtenirPointsCampagne()
{
	return pointsCampagne;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline int FacadeModele::obtenirPointsBille()
///
/// Cette fonction retourne le nombre de points requis pour avoir une bille gratuite
///
/// @return le nombre de points requis pour avoir une bille gratuite
///
////////////////////////////////////////////////////////////////////////
inline int FacadeModele::obtenirPointsBille()
{
	return pointsBille;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline int FacadeModele::obtenirDifficulté()
///
/// Cette fonction retourne la difficulté
///
/// @return La difficulte
///
////////////////////////////////////////////////////////////////////////
inline int FacadeModele::obtenirDifficulté()
{
	return difficulte;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void FacadeModele::assignerPointsCampagne(int point)
///
/// Cette fonction assigne le nombre de points requis pour passer a la campagne suivante
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void FacadeModele::assignerPointsCampagne(int point)
{
	pointsCampagne = point;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void FacadeModele::assignerPointsBille(int point)
///
/// Cette fonction assigne le nombre de points requis pour obtenir une bille gratuite
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void FacadeModele::assignerPointsBille(int point)
{
	pointsBille = point;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void FacadeModele::assignerDifficulte(int point)
///
/// Cette fonction assigne la diffculte
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void FacadeModele::assignerDifficulte(int point)
{
	difficulte = point;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline const ArbreRenduINF2990* FacadeModele::obtenirArbreRenduINF2990() const
///
/// Cette fonction retourne l'arbre de rendu de la scène (version constante
/// de la fonction).
///
/// @return L'arbre de rendu de la scène.
///
////////////////////////////////////////////////////////////////////////
inline const ArbreRenduINF2990* FacadeModele::obtenirArbreRenduINF2990() const
{
   return arbre_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline ArbreRenduINF2990* FacadeModele::obtenirArbreRenduINF2990()
///
/// Cette fonction retourne l'arbre de rendu de la scène (version non constante
/// de la fonction).
///
/// @return L'arbre de rendu de la scène.
///
////////////////////////////////////////////////////////////////////////
inline ArbreRenduINF2990* FacadeModele::obtenirArbreRenduINF2990()
{
   return arbre_;
}


#endif // __APPLICATION_FACADEMODELE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
