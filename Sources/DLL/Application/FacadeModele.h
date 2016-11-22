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
#include "../Arbre/Visiteurs/VisiteurCollision.h"
#include "FTGL/ftgl.h"
#include "QuadTree.h"
#include "Son.h"
#include "BoiteEnvironnement.h"

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

   /// sortie console de la vitesse de la bille
   inline void sortieConsoleVitesse(NoeudBille* bille);
   /// sortie console de la lumiere
   inline void sortieConsoleLumiere();
   /// sortie console de la creation de bille
   inline void sortieConsoleCreationBille(NoeudBille* bille);

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
   /// Affiche le texte FTGL de la scene pour le nombre de points
   void afficherTextePoints() const;
   /// Affiche le texte FTGL de la scene pour le nombre de bille
   void afficherTexteBille() const;
 
   /// Retourne la vue courante.
   inline vue::Vue* obtenirVue();
   /// Retourne l'arbre de rendu.
   inline const ArbreRenduINF2990* obtenirArbreRenduINF2990() const;
   /// Retourne l'arbre de rendu.
   inline ArbreRenduINF2990* obtenirArbreRenduINF2990();
   /// Retourne le son.
   inline Son* obtenirSon() const;
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
   /// relache les visiteurs
   void releaseVisiteurs();
   /// Réinitialise la scène.
   void reinitialiser();
   /// Permet la mise à l'échelle des objets de la scène
   void scale(glm::dvec3 point);
   /// Permet de supprimer les objets selectionnés
   void supprimer();
   /// Permet d'incrementer les points
   void incrementPoints(int points);
   /// retourne lenombre de points actuel
   int obtenirPoints();
   /// reinitialise lespoints
   void resetPoints();
   /// cree une bille a partir d'un generateur de bille
   void creerBille();
   /// retourne le nombre de billets restante
   int obtenirBillesRestantes() const;
   /// assigne le nombre de billes
   void assignerNbBillesRestante(int billes);
   /// decremente le nombre de bille sur la table
   void decrementerBilleSurLaTable();
   /// Anime la scène.
   void animer(float temps);
   /// assigne le nombre maximale de bille sur la table
   void assignerBillesMax(int billes);
   /// active/deactive les affichages consoles
   inline void assignerAffichageDebug(bool affiche);
   /// active/deactive les affichages de vitesse apres collisions
   inline void assignerAffichageVitesse(bool affiche);
   /// active/deactive les affichages de creation billes
   inline void assignerAffichageCreationBille(bool affiche);
   /// active/deactive les affichages de lumiere
   inline void assignerAffichageLumiere(bool affiche);
   /// active/deactive les affichages des champ portails
   inline void assignerAffichageChampPortail(bool affiche);
   /// permet de savoir si on oit afficher les champs des portails
   inline bool obtenirAfficherChampPortail();
   /// retourne le nombre de billes en jeu
   inline int obtenirBillesEnJeu();
   // assigne la valeur du joueur virtuel
   inline void assignerJoueurVirtuel(bool valeur);
   // retourne la valeur du joueur virtuel
   inline bool obtenirJoueurVirtuel() const;
   /// Inverse la condition d'affichage du texte
   void inverserAffichageTexte();

   // assigne l'état de la lumière ambiante
   inline void assignerLumAmbiante();
   // retourne l'état de la lumière ambiante
   inline bool obtenirLumAmbiante() const;

   // assigne l'état de la lumière directionnelle
   inline void assignerLumDirect();
   // retourne l'état de la lumière directionnelle
   inline bool obtenirLumDirect() const;

   // assigne l'état des projecteurs
   inline void assignerLumSpot();
   // retourne l'état des projecteurs
   inline bool obtenirLumSpot() const;

   /// XML /////////////////////////////////////////////

   /// verifier la présence des objets nécessaires
   bool sauvegardePossible();

   /// gère la sauvegarde de la zone de jeu en fichier XML
   bool sauvegardeArbreXML(std::string nomFichier);

   /// lire le XML
   bool lectureXML(char* nomFichier);

   // permet d'acceder au QuadTree
   QuadTree* obtenirQuadTree();

   //reinitialise la partie en cour
   void reinitialiserPartie();

   int FacadeModele::obtenirDifficulteDuXML(char* nomFichier);

   //Change la vue à Perspective
   void FacadeModele::changeToPerspective();
   
   // Change la vue à Ortho
   void FacadeModele::changeToOrtho();


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

   /// Nom du fichier XML dans lequel doit se trouver la configuration.
   static const std::string FICHIER_CONFIGURATION;

   /// Pointeur vers l'instance unique de la classe.
   static FacadeModele* instance_;

   /// Pointeur vers le visiteur de translation
   VisiteurMouvement* visiteurMouvement_{ nullptr };
   VisiteurCollision* visiteurCollision_{ nullptr };

   /// Pointeur vers le visiteur de lire XML
   VisiteurLireXML* visiteurLireXML{ nullptr };
   /// Pointeur vers le visiteur pour écrire XML
   VisiteurEcrireXML* visiteurEcrireXML{ nullptr };

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
   /// utilitaire de son
   Son* son_{nullptr};
   ///QuadTree pour le calcul des collision
   QuadTree* quadTree_{ nullptr };

   /// Determine si l'on doit afficher la position initial de la bille pour le debug
   bool afficherPos = true;
   /// Point courant de la partie
   int points = 0;
   /// nb de billes a jouer
   int billesRestantes = 9999;
   /// billes actives en jeu
   int billesEnJeu = 0;
   /// billes actives max en jeu
   int billesMax = 1;
   /// determine si les affichage de deboguages sont actiees
   bool affichageDebug = false;
   /// determine si les affichage de deboguages de vitesse de billes apres collisions sont actiees
   bool affichageVitesse = false;
   /// determine si les affichage de deboguages de creation de billes sont actiees
   bool affichageCreation = false;
   /// determine si les champs d'attractions des portails sont actiees
   bool affichageChampPortail = false;
   /// compteur pour les sortie de doubles boules
   int compteurDeuxiemeBoule = 0;
   /// determine si joueur virtuel actif
   bool joueurVirtuelActif = false;
   /// Indique si l'affichage de texte doit etre actif ou non
   bool peutAfficher = false;

   /// determine si l'éclairage ambiant est actif
   bool lumAmbiantActif = true;
   /// determine si l'éclairage directionnelle est actif
   bool lumDirectActif = true;
   /// determine si l'éclairage spot est actif
   bool lumSpotActif = true;

   /// skybox
   utilitaire::BoiteEnvironnement* skybox_;
   ///Font pour l'affichage des points
   FTFont* myfontPoints;
   ///Font pour l'affichage de texte
   FTFont* myfontBille;
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

////////////////////////////////////////////////////////////////////////
///
/// @fn inline const Son* FacadeModele::obtenirSon() const
///
/// Cette fonction retourne l'utilitaire de son
///
/// @return L'utilitaire de son.
///
////////////////////////////////////////////////////////////////////////
inline Son* FacadeModele::obtenirSon() const
{
	return son_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void FacadeModele::AssignerAffichageDebug(bool affiche)
///
/// Cette fonction active/deactive les affichages consoles
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
inline void FacadeModele::assignerAffichageDebug(bool affiche)
{
	affichageDebug = affiche;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void FacadeModele::AssignerAffichageVitesse(bool affiche)
///
/// Cette fonction active/deactive les affichages de vitesse apres collisions
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
inline void FacadeModele::assignerAffichageVitesse(bool affiche)
{
	affichageVitesse = affiche;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void FacadeModele::AssignerAffichageCreationBille(bool affiche);
///
/// Cette fonction active/deactive les affichages de creation billes
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
inline void FacadeModele::assignerAffichageCreationBille(bool affiche)
{
	affichageCreation = affiche;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void FacadeModele::AssignerAffichageChampPortail(bool affiche)
///
/// Cette fonction active/deactive les affichages des champ portails
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
inline void FacadeModele::assignerAffichageChampPortail(bool affiche)
{
	affichageChampPortail = affiche;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline static void FacadeModele::sortieConsoleVitesse(NoeudBille* bille)
///
/// Cette fonction affiche la vitesse dune bille a la console
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
inline void FacadeModele::sortieConsoleVitesse(NoeudBille* bille)
{
	if (affichageDebug && affichageVitesse)
	{
		SYSTEMTIME temps;
		GetSystemTime(&temps);
		float millis = temps.wMilliseconds;
		float secondes = temps.wSecond;
		float minutes = temps.wMinute;
		float heures = temps.wHour - 5;
		int x = bille->obtenirVitesseX();
		int y = bille->obtenirVitesseY();
		float vitesse = std::sqrt(x*x + y*y);
		std::cout << heures << ":" << minutes << ":" << secondes << ":" << millis <<
			" - Vitesse: " << vitesse << std::endl;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline static void FacadeModele::sortieConsoleCreationBille(NoeudBille* bille)
///
/// Cette fonction affiche position de creation d'une nouvellebille
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
inline void FacadeModele::sortieConsoleCreationBille(NoeudBille* bille)
{
	if (affichageDebug && affichageCreation)
	{
		SYSTEMTIME temps;
		GetSystemTime(&temps);
		float millis = temps.wMilliseconds;
		float secondes = temps.wSecond;
		float minutes = temps.wMinute;
		float heures = temps.wHour;
		glm::dvec3 pos = bille->obtenirPositionRelative();
		std::cout << heures << ":" << minutes << ":" << secondes << ":" << millis <<
			" - Nouvelle Bille: x: " << pos.x << " y: " << pos.y << std::endl;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline static void FacadeModele::obtenirAfficherChampPortail()
///
/// Cette fonction permet de savoirsion doitafficher le champ d'attraction des portails
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
inline bool FacadeModele::obtenirAfficherChampPortail()
{
	return affichageChampPortail;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline static void FacadeModele::obtenirBillesEnJeu()
///
/// Cette fonction permet de savoir combien de billes sont sur la table
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
inline int FacadeModele::obtenirBillesEnJeu()
{
	return billesEnJeu;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void FacadeModele::assignerJoueurVirtuel(bool valeur)
///
/// Cette fonction assigne la valeur du joueur virtuel
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
inline void FacadeModele::assignerJoueurVirtuel(bool valeur)
{
	joueurVirtuelActif = valeur;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn iinline bool FacadeModele::obtenirJoueurVirtuel() const
///
/// Cette fonction retourne la valeur du joueur virtuel
///
/// @return valeur
///
////////////////////////////////////////////////////////////////////////
inline bool FacadeModele::obtenirJoueurVirtuel() const
{
	return joueurVirtuelActif;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void FacadeModele::assignerLumAmbiante()
///
/// Cette fonction assigne l'état de la lumière ambiante
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
inline void FacadeModele::assignerLumAmbiante()
{
	lumAmbiantActif = !lumAmbiantActif;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn iinline bool FacadeModele::obtenirLumAmbiante() const
///
/// Cette fonction retourne l'état de la lumière ambiante
///
/// @return valeur
///
////////////////////////////////////////////////////////////////////////
inline bool FacadeModele::obtenirLumAmbiante() const
{
	return lumAmbiantActif;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void FacadeModele::assignerLumDirect()
///
/// Cette fonction assigne l'état de la lumière directionnelle
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
inline void FacadeModele::assignerLumDirect()
{
	lumDirectActif = !lumDirectActif;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn iinline bool FacadeModele::obtenirLumDirect() const
///
/// Cette fonction retourne l'état de la lumière directionnelle
///
/// @return valeur
///
////////////////////////////////////////////////////////////////////////
inline bool FacadeModele::obtenirLumDirect() const
{
	return lumDirectActif;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void FacadeModele::assignerLumSpot()
///
/// Cette fonction assigne l'état des projecteurs
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
inline void FacadeModele::assignerLumSpot()
{
	lumSpotActif = !lumSpotActif;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn iinline bool FacadeModele::obtenirLumSpot() const
///
/// Cette fonction retourne l'état des projecteurs
///
/// @return valeur
///
////////////////////////////////////////////////////////////////////////
inline bool FacadeModele::obtenirLumSpot() const
{
	return lumSpotActif;
}


#endif // __APPLICATION_FACADEMODELE_H__
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
