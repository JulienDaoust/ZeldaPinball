////////////////////////////////////////////////
/// @file   FacadeInterfaceNative.cpp
/// @author INF2990
/// @date   2014-08-16
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////
#include "FacadeInterfaceNative.h"
#include "FacadeModele.h"

#include "glm\glm.hpp"
#include "FacadeModele.h"
#include "AideGL.h"
#include "Vue.h"
#include "ArbreRenduINF2990.h"
#include "NoeudPlaque.h"
#include "NoeudPaletteJoueur1Gauche.h"
#include "NoeudPaletteJoueur1Droite.h"
#include "NoeudPaletteJoueur2Gauche.h"
#include "NoeudPaletteJoueur2Droite.h"
#include "NoeudRessort.h"
#include "CompteurAffichage.h"
#include <iostream>
#include <string>
#include <fstream>
#include "BancTests.h"

extern "C"
{
	////////////////////////////////////////////////////////////////////////
	///
	/// __declspec(dllexport) void __cdecl initialiserOpenGL(int* handle)
	///
	/// Cette fonction initialise un contexte OpenGL dans la fenêtre
	/// identifiée par le handle passé en paramètre.  Cette fonction doit
	/// être la première à être appelée, car la création de l'objet du modèle
	/// C++ s'attend à avoir un contexte OpenGL valide.
	///
	/// @param[in] handle : Le handle.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl initialiserOpenGL(int* handle)
	{
		if (handle == nullptr)
			return;

		FacadeModele::obtenirInstance()->initialiserOpenGL((HWND) handle);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl libererOpenGL()
	///
	/// Cette fonction libère le contexte OpenGL. Cette fonction doit être la
	/// dernière à être appelée, car elle libère également l'objet du modèle
	/// C++.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl libererOpenGL()
	{
		FacadeModele::obtenirInstance()->libererOpenGL();

		// Désinitialisation de la façade.  Le fait de le faire après la
		// désinitialisation du contexte OpenGL aura pour conséquence que la
		// libération des listes d'affichages, par exemple, sera faite une fois que
		// le contexte n'existera plus, et sera donc sans effet.
		FacadeModele::libererInstance();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl dessinerOpenGL()
	///
	/// Cette fonction affiche la scène.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl dessinerOpenGL()
	{
		// Affiche la scène.
		FacadeModele::obtenirInstance()->afficher();

		// Temporaire: pour détecter les erreurs OpenGL
		aidegl::verifierErreurOpenGL();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// __declspec(dllexport) void __cdecl redimensionnerFenetre(int largeur, int hauteur)
	///
	/// Cette fonction doit être appelée lorsque la fenêtre est
	/// redimensionnée afin d'ajuster les paramètres de la machine à états
	/// d'OpenGL pour correspondre aux nouvelles dimensions de la fenêtre.
	///
	/// @param[in] largeur : La nouvelle largeur de la fenêtre.
	/// @param[in] hauteur : La nouvelle hauteur de la fenêtre.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl redimensionnerFenetre(int largeur, int hauteur)
	{
		
		FacadeModele::obtenirInstance()->obtenirVue()->redimensionnerFenetre(
			glm::ivec2{ 0, 0 },
			glm::ivec2{ largeur, hauteur }
		);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl animer(double temps)
	///
	/// Cette fonction effectue les différents calculs d'animations
	/// nécessaires pour le mode jeu, tel que les différents calculs de
	/// physique du jeu.
	///
	/// @param[in] temps : Intervalle de temps sur lequel effectuer le calcul.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl animer(double temps)
	{
		FacadeModele::obtenirInstance()->animer((float) temps);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl zoomIn()
	///
	/// Cette fonction applique un zoom avant sur le présent volume de vision.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl zoomIn()
	{
		FacadeModele::obtenirInstance()->obtenirVue()->zoomerIn();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl zoomOut()
	///
	/// Cette fonction applique un zoom arrière sur le présent volume de vision.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl zoomOut()
	{
		FacadeModele::obtenirInstance()->obtenirVue()->zoomerOut();
	}

	//////////////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) translater(double deplacementX, double deplacementY)
	///
	/// Cette fonction applique une translation en x et y selon les touches clavier
	///
	/// @return Aucune.
	///
	//////////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl translater(double deplacementX, double deplacementY)
	{
		FacadeModele::obtenirInstance()->obtenirVue()->deplacerXY(deplacementX, deplacementY);
	}

	//////////////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) translater(double deplacementX, double deplacementY)
	///
	/// Cette fonction applique une translation en x et y selon les touches clavier
	///
	/// @return Aucune.
	///
	//////////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl translaterSouris(double deplacementSourisX, double deplacementSourisY)
	{
		FacadeModele::obtenirInstance()->obtenirVue()->deplacerXY(deplacementSourisX, deplacementSourisY);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) int __cdecl obtenirAffichagesParSeconde()
	///
	/// Cette fonction permet d'obtenir le nombre d'affichages par seconde.
	///
	/// @return Le nombre d'affichage par seconde.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirAffichagesParSeconde()
	{
		return utilitaire::CompteurAffichage::obtenirInstance()->obtenirAffichagesSeconde();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) bool __cdecl executerTests()
	///
	/// Cette fonction permet d'exécuter l'ensemble des tests unitaires
	///
	/// @return 0 si tous les tests ont réussi, 1 si au moins un test a échoué
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool __cdecl executerTests()
	{
		bool reussite = BancTests::obtenirInstance()->executer();
		return reussite ? 0 : 1;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl ajouterNoeud(std::string nom)
	///
	/// Cette fonction permet ajouter un noeud a l'arbre de rendu
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl ajouterNoeud(char* nom,int x, int y)
	{
		std::string type(nom);
		glm::dvec3 point;
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, point);
		FacadeModele::obtenirInstance()->ajouterNoeud(nom,point);
		
	}

	/////////////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl ZoomInRectangle(std::string nom)
	///
	/// Cette fonction permet d'effectuer un zoom ï¿½ l'aide de sï¿½lection rectangulaire
	///
	/////////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl ZoomInRectangle(int minX, int minY, int maxX, int maxY)
	{
		glm::dvec3 pointMin;
		glm::dvec3 pointMax;
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(minX, minY, pointMin);
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(maxX, maxY, pointMax);
		FacadeModele::obtenirInstance()->obtenirVue()->zoomerInElastique(pointMin, pointMax);
	}

	///////////////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl ZoomOutRectangle(std::string nom)
	///
	/// Cette fonction permet d'effectuer un zoom ï¿½ l'aide de sï¿½lection rectangulaire
	///
	///////////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl ZoomOutRectangle(int minX, int minY, int maxX, int maxY)
	{
		glm::dvec3 pointMin;
		glm::dvec3 pointMax;
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(minX, minY, pointMin);
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(maxX, maxY, pointMax);
		FacadeModele::obtenirInstance()->obtenirVue()->zoomerOutElastique(pointMin, pointMax);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl ajouterMur(int x1, int y1, int x2, int y2)
	///
	/// Cette fonction permet ajouter un noeud a l'arbre de rendu
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl ajouterNoeudMur(int x1, int y1, int x2, int y2)
	{
		glm::dvec3 point1;
		glm::dvec3 point2;
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x1, y1, point1);
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x2, y2, point2);
		FacadeModele::obtenirInstance()->ajouterNoeudMur(point1, point2);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl selectionSimple(int x, int y)
	///
	/// Cette fonction permet de selectionner un objet
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl selectionSimple(int x, int y)
	{
		glm::dvec3 point;
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, point);
		FacadeModele::obtenirInstance()->selectionSimple(point);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl selectionMultiple(int gauche, int haut, int droite, int bas)
	///
	/// Cette fonction permet de selectionner un ou plusieurs objets
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl selectionMultiple(int gauche, int haut, int droite, int bas)
	{
		glm::dvec3 min;
		glm::dvec3 max;
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(gauche, bas, min);
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(droite, haut, max);
		FacadeModele::obtenirInstance()->selectionMultiple(min, max);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl deselectionnerTout()
	///
	/// Cette fonction permet de deselectionner tout lesobjets de l'arbre
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl deselectionnerTout()
	{
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->deselectionnerTout();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl RetournerPosition(int x, int y)
	///
	/// Cette fonction permet de retourner une position sur linterface en position sur la cloture virtuelle
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl RetournerPosition(int x, int y)
	{
		glm::dvec3 point;
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, point);
		
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl RetournerPosition(int x, int y)
	///
	/// Cette fonction permet de retourner une position sur linterface en position sur la cloture virtuelle
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool __cdecl survolPlaque(int x, int y)
	{
		glm::dvec3 point;
		NoeudAbstrait* noeudPlaque;
		BoiteEnglobante boitePlaque;

		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, point);
		noeudPlaque = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher("plaque");

		boitePlaque = noeudPlaque->obtenirBoiteEnglobante();
		return utilitaire::DANS_LIMITESXY(point[0], boitePlaque.coinBG[0], boitePlaque.coinBD[0], point[1], boitePlaque.coinBG[1],boitePlaque.coinHG[1]);

	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn	__declspec(dllexport) void __cdecl translation(int x1, int y1, int x2, int y2)
	///
	/// Cette fonction permet de bouger un objet
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl translation(int x1, int y1,  int x2, int y2)
	{
		glm::dvec3 pointDepart;
		glm::dvec3 pointFinal;

		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x1, y1, pointDepart);
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x2, y2, pointFinal);

		FacadeModele::obtenirInstance()->translation(pointFinal - pointDepart);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn	__declspec(dllexport) void __cdecl translationX(int x)
	///
	/// Cette fonction permet de bouger un objet sur l'axe des x
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl translationX(int x)
	{
		glm::dvec3 pointDepart;
		glm::dvec3 pointFinal;


		ArbreRenduINF2990* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
		std::vector<NoeudAbstrait*> vectNoeud = arbre->obtenirNoeudSelectionnes();
		NoeudAbstrait* noeud = *(vectNoeud.begin());
		pointDepart = noeud->obtenirPositionRelative();

		pointFinal.y = pointDepart.y;
		pointFinal.x = pointDepart.x + x;

		FacadeModele::obtenirInstance()->translation(pointFinal - pointDepart);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn	__declspec(dllexport) void __cdecl translationX(int x)
	///
	/// Cette fonction permet de bouger un objet sur l'axe des x
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl translationY(int y)
	{
		glm::dvec3 pointDepart;
		glm::dvec3 pointFinal;


		ArbreRenduINF2990* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
		std::vector<NoeudAbstrait*> vectNoeud = arbre->obtenirNoeudSelectionnes();
		NoeudAbstrait* noeud = *(vectNoeud.begin());
		pointDepart = noeud->obtenirPositionRelative();

		pointFinal.x = pointDepart.x;
		pointFinal.y = pointDepart.y + y;

		FacadeModele::obtenirInstance()->translation(pointFinal - pointDepart);
	}

	////////////////////////////////////////////////////////////////////////////////
	/// @fn	__declspec(dllexport) void __cdecl translationSouris(int x, int y)
	///
	/// Cette fonction permet de bouger un objet
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl translationSouris(int x1, int y1, int x2, int y2)
	{
		glm::dvec3 pointDepart;
		glm::dvec3 pointFinal;

		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x1, y1, pointDepart);
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x2, y2, pointFinal);

		FacadeModele::obtenirInstance()->translation(pointFinal - pointDepart);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn	__declspec(dllexport) void __cdecl releaseVisiteur()
	///
	/// Cette fonction permet de relacher le Visiteur de translation (translation terminée)
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl releaseVisiteurs()
	{
		FacadeModele::obtenirInstance()->releaseVisiteurs();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn	__declspec(dllexport) void __cdecl validateMouvement()
	///
	/// Cette fonction permet de s'assurer que tout lesobjets sont sur la surface
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl validateMouvement()
	{
		FacadeModele::obtenirInstance()->validateMouvement();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn	__declspec(dllexport) void __cdecl rotation(double angle)
	///
	/// Cette fonction permet d'effectuer une rotation sur un ou plusieurs objets
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl rotation(double angle)
	{
		FacadeModele::obtenirInstance()->rotation(angle);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn	__declspec(dllexport) void __cdecl rotation(double angle)
	///
	/// Cette fonction permet d'effectuer une rotation sur la caméra
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl rotaterXY(double rotationX, double rotationY)
	{
		FacadeModele::obtenirInstance()->obtenirVue()->rotaterXY(rotationX, rotationY);
	}

	////////////////////////////////////////////////////////////////////////
	///
	////////////////////////////////////////////////////////////////////////
	///
	/// @fn    __declspec(dllexport) void __cdecl rotationSimple(double angle)
	///
	/// Cette fonction permet d'effectuer une rotation sur un objet
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl rotationSimple(double angle)
	{
		ArbreRenduINF2990* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
		std::vector<NoeudAbstrait*> vectNoeud = arbre->obtenirNoeudSelectionnes();
		NoeudAbstrait* noeud = *(vectNoeud.begin());
		noeud->assignerAngleRotation(angle);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn	__declspec(dllexport) bool __cdecl ÉcritureXML(char* nomFicher)
	///
	/// Cette fonction permet l'écriture du jeu sous format XML
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool __cdecl ecritureXML(char* nomFichier)
	{
		if (FacadeModele::obtenirInstance()->sauvegardePossible())
		{
			FacadeModele::obtenirInstance()->sauvegardeArbreXML(nomFichier);
			return true;
		}

		return false;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn	__declspec(dllexport) bool __cdecl ÉcritureXML(char* nomFicher)
	///
	/// Cette fonction permet l'écriture du jeu sous format XML
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool __cdecl estSauvegardable()
	{
		return FacadeModele::obtenirInstance()->sauvegardePossible();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn	__declspec(dllexport) bool __cdecl lireXML(char* nomFicher)
	///
	/// Cette fonction permet la lecture du jeu sous format XML
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool __cdecl lireXML(char* nomFichier)
	{
		return FacadeModele::obtenirInstance()->lectureXML(nomFichier);	
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn	__declspec(dllexport) void __cdecl scaling(int x, int y)
	///
	/// Cette fonction permet la mise a l'échelle des objets de la scene
	///
	/// @param[in] int x, int y : Coordonnées de la souris
	///
	/// @return Aucune.
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl scaling(int x, int y)
	{
		glm::dvec3 point;

		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, point);
		FacadeModele::obtenirInstance()->scale(point);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn	__declspec(dllexport) void __cdecl duplication(int x, int y)
	///
	/// Cette fonction permet la duplication des objects selectionnées de la scene
	///
	/// @param[in] int x, int y : Coordonnées de la souris
	///
	/// @return Aucune.
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl duplication(int x, int y)
	{
		glm::dvec3 point;

		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, point);
		FacadeModele::obtenirInstance()->duplication(point);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn	__declspec(dllexport) void __cdecl supprimerObjets()
	///
	/// Cette fonction permet de supprimer les objets sélectionnées
	///
	/// @param[in] int x, int y : Coordonnées de la souris
	///
	/// @return Aucune.
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl supprimerObjets()
	{
		FacadeModele::obtenirInstance()->supprimer();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl ajouterNoeudPortail(int x1, int y1, int x2, int y2)
	///
	/// Cette fonction permet ajouter un noeud a l'arbre de rendu
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl ajouterNoeudPortail(int x1, int y1, int x2, int y2)
	{
		glm::dvec3 point1;
		glm::dvec3 point2;
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x1, y1, point1);
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x2, y2, point2);
		FacadeModele::obtenirInstance()->ajouterNoeudPortail(point1, point2);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl estSelectionne()
	///
	/// Cette fonction permet de verifier combien de noeuf de l'arbre sont selectionne
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl estSelectionne()
	{
		return FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirNoeudSelectionnes().size();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn	__declspec(dllexport) void __cdecl miseEchelle(double angle)
	///
	/// Cette fonction permet d'effectuer une rotation sur un objet
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl miseEchelle(double scale)
	{
		FacadeModele::obtenirInstance()->miseEchelle(scale);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn	__declspec(dllexport) int __cdecl obtenirPointsButoireCirculaire()
	///
	/// Cette fonction permet d'obtenir les points du butoire circulaire
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirPointsButoireCirculaire()
	{
		ArbreRenduINF2990* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
		return 1;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn	__declspec(dllexport) void __cdecl reinitialiser()
	///
	/// Cette fonction permet de reinitialiser l'arbre de rendu
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl reinitialiser()
	{
		FacadeModele::libererInstance();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn	__declspec(dllexport) void __cdecl animerPaletteGJ1(bool sound)
	///
	/// Cette fonction permet d'animer la palette gauche du joueur 1
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl animerPaletteGJ1(bool sound)
	{
		std::vector<NoeudAbstrait*> vectNoeud = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirNoeudPaletteGJ1();
		std::vector<NoeudAbstrait*>::iterator it;
		NoeudPaletteJoueur1Gauche* noeudPalette;
		for (it = vectNoeud.begin(); it < vectNoeud.end(); it++)
		{
			noeudPalette = (NoeudPaletteJoueur1Gauche*) (*it);
			noeudPalette->setAnimation();
		}
		if (sound)
			FacadeModele::obtenirInstance()->obtenirSon()->sonPalette();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn	__declspec(dllexport) void __cdecl animerPaletteDJ1(bool sound)
	///
	/// Cette fonction permet d'animer la palette droite du joueur 1
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl animerPaletteDJ1(bool sound)
	{
		std::vector<NoeudAbstrait*> vectNoeud = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirNoeudPaletteDJ1();
		std::vector<NoeudAbstrait*>::iterator it;
		NoeudPaletteJoueur1Droite* noeudPalette;
		for (it = vectNoeud.begin(); it < vectNoeud.end(); it++)
		{
			noeudPalette = (NoeudPaletteJoueur1Droite*)(*it);
			noeudPalette->setAnimation();
		}
		if (sound)
			FacadeModele::obtenirInstance()->obtenirSon()->sonPalette();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn	__declspec(dllexport) void __cdecl animerPaletteGJ2(bool sound)
	///
	/// Cette fonction permet d'animer la palette gauche du joueur 2
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl animerPaletteGJ2(bool sound)
	{
		std::vector<NoeudAbstrait*> vectNoeud = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirNoeudPaletteGJ2();
		std::vector<NoeudAbstrait*>::iterator it;
		NoeudPaletteJoueur2Gauche* noeudPalette;
		for (it = vectNoeud.begin(); it < vectNoeud.end(); it++)
		{
			noeudPalette = (NoeudPaletteJoueur2Gauche*)(*it);
			noeudPalette->setAnimation();
		}
		if (sound)
			FacadeModele::obtenirInstance()->obtenirSon()->sonPalette();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn	__declspec(dllexport) void __cdecl animerPaletteDJ2(bool sound)
	///
	/// Cette fonction permet d'animer la palette droite du joueur 2
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl animerPaletteDJ2(bool sound)
	{
		std::vector<NoeudAbstrait*> vectNoeud = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirNoeudPaletteDJ2();
		std::vector<NoeudAbstrait*>::iterator it;
		NoeudPaletteJoueur2Droite* noeudPalette;
		for (it = vectNoeud.begin(); it < vectNoeud.end(); it++)
		{
			noeudPalette = (NoeudPaletteJoueur2Droite*)(*it);
			noeudPalette->setAnimation();
		}
		if (sound)
			FacadeModele::obtenirInstance()->obtenirSon()->sonPalette();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn	__declspec(dllexport) void __cdecl reinitialiserPartie()
	///
	/// Cette fonction permet de reinitialiser la partie
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl reinitialiserPartie()
	{
		FacadeModele::obtenirInstance()->reinitialiserPartie();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn	__declspec(dllexport) void __cdecl obtenirDifficulte(char* nomFichier)
	///
	/// Cette fonction nous donne la dificulte d'une zone en particulié dont le 
	/// path est nomFichier
	///
	///param[in] string : le nom du fichier pour la lecture de la difficulte
	///
	/// @return int : la difficulte de la zone si la zone est valide,
	///				  -1 si la zone est invalide
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirDifficulte(char* nomFichier)
	{
		return FacadeModele::obtenirInstance()->obtenirDifficulteDuXML(nomFichier);	
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn	__declspec(dllexport) void __cdecl assignerNbBillesActuel()
	///
	/// Cette fonction fixe le nombre de billes dans las réserve de billes
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl assignerNbBillesInitial(int nbBilles)
	{
		FacadeModele::obtenirInstance()->assignerNbBillesRestante(nbBilles);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn	__declspec(dllexport) void __cdecl obtenirNbBillesActuel()
	///
	/// Cette fonction nous donne le nombre de billes actuellement dans las réserve de billes
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirNbBillesActuel()
	{
		return FacadeModele::obtenirInstance()->obtenirBillesRestantes();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn	__declspec(dllexport) void __cdecl getPointageActuel()
	///
	/// Cette fonction nous donne le nombre de point actuellement accumulé dans la zone actuelle
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirPointageActuel()
	{
		return FacadeModele::obtenirInstance()->obtenirPoints();

	}
	////////////////////////////////////////////////////////////////////////
	///
	/// @fn	__declspec(dllexport) void __cdecl assignerDebug(bool* dbug)
	///
	/// Cette fonction permet de reinitialiser la partie
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl assignerDebug(bool* dbug)
	{
	}


	////////////////////////////////////////////////////////////////////////
	/// @fn	__declspec(dllexport) void __cdecl animerRessort(bool animer)
	///
	/// Cette fonction permet d'animer le ressort
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl animerRessort(bool animer)
	{
		std::vector<NoeudAbstrait*> vectNoeud = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirNoeudRessort();
		std::vector<NoeudAbstrait*>::iterator it;
		NoeudRessort* noeudRessort;
		for (it = vectNoeud.begin(); it < vectNoeud.end(); it++)
		{
			noeudRessort = (NoeudRessort*)(*it);
			noeudRessort->assignerRetraction(animer);
		}
		if (animer)
			FacadeModele::obtenirInstance()->obtenirSon()->sonSpringDown();
		else
			FacadeModele::obtenirInstance()->obtenirSon()->sonSpringUp();
	}


	////////////////////////////////////////////////////////////////////////
	/// @fn	__declspec(dllexport) void __cdecl assignerBillesRestantes(int billes)
	///
	/// Cette fonction assigne le nombre de billes pour une partie
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl assignerBillesRestantes(int billes)
	{
		FacadeModele::obtenirInstance()->assignerNbBillesRestante(billes);
	}
	////////////////////////////////////////////////////////////////////////
	/// @fn	__declspec(dllexport) void __cdecl assignerBillesMax(int billes)
	///
	/// Cette fonction assigne le nombre de billes maximale sur la table
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl assignerBillesMax(int billes)
	{
		FacadeModele::obtenirInstance()->assignerBillesMax(billes);
	}
	////////////////////////////////////////////////////////////////////////
	/// @fn	__declspec(dllexport) void __cdecl assignerAffichageDebug(bool affiche)
	///
	/// Cette fonction permet d'activer/deactiver les sorties consoles
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl assignerAffichageDebug(bool affiche)
	{
		FacadeModele::obtenirInstance()->assignerAffichageDebug(affiche);
	}

	////////////////////////////////////////////////////////////////////////
	/// @fn	__declspec(dllexport) void __cdecl assignerAffichageVitesse(bool affiche)
	///
	/// Cette fonction permet d'activer/deactiver les sorties consoles de vitesse de bille
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl assignerAffichageVitesse(bool affiche)
	{
		FacadeModele::obtenirInstance()->assignerAffichageVitesse(affiche);
	}

	////////////////////////////////////////////////////////////////////////
	/// @fn	__declspec(dllexport) void __cdecl assignerAffichageCreationBille(bool affiche)
	///
	/// Cette fonction permet d'activer/deactiver les sorties consoles de creation de billes
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl assignerAffichageCreationBille(bool affiche)
	{
		FacadeModele::obtenirInstance()->assignerAffichageCreationBille(affiche);
	}

	////////////////////////////////////////////////////////////////////////
	/// @fn	__declspec(dllexport) void __cdecl assignerAffichagePortail(bool affiche)
	///
	/// Cette fonction permet d'activer/deactiver les affichage des champs dattractions des portails
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl assignerAffichagePortail(bool affiche)
	{
		FacadeModele::obtenirInstance()->assignerAffichageChampPortail(affiche);
	}

	////////////////////////////////////////////////////////////////////////
	/// @fn	__declspec(dllexport) void __cdecl assignerPointsButoireCirculaire(int point)
	///
	/// Cette fonction permet d'assigner les points du butoire circulaire
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl assignerPointsButoirCirculaire(int point)
	{
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->assignerPointsButoirCir(point);
	}

	////////////////////////////////////////////////////////////////////////
	/// @fn	__declspec(dllexport) void __cdecl assignerPointsButoireTriangulaire(int point)
	///
	/// Cette fonction permet d'assigner les points du butoire triangulaire
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl assignerPointsButoirTriangulaire(int point)
	{
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->assignerPointsButoirTri(point);
	}

	////////////////////////////////////////////////////////////////////////
	/// @fn	__declspec(dllexport) void __cdecl assignerPointsCible(int point)
	///
	/// Cette fonction permet d'assigner les points du butoire Cible
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl assignerPointsCible(int point)
	{
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->assignerPointsCible(point);
	}

	////////////////////////////////////////////////////////////////////////
	/// @fn	__declspec(dllexport) void __cdecl assignerPointsNiveauSuivant(int point)
	///
	/// Cette fonction permet d'assigner les points pour passer au niveau suivant
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl assignerPointsNiveauSuivant(int point)
	{
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->assignerPointsCampagne(point);
	}

	////////////////////////////////////////////////////////////////////////
	/// @fn	__declspec(dllexport) void __cdecl assignerPointsNiveauSuivant(int point)
	///
	/// Cette fonction permet d'assigner les points du butoire Cible
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl assignerPointsBilleBonus(int point)
	{
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->assignerPointsBille(point);
	}

	////////////////////////////////////////////////////////////////////////
	/// @fn	__declspec(dllexport) void __cdecl pointsNiveauSuivant()
	///
	/// Cette fonction permet de savoir si on a assez de points pour passer a lapartie suivante
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl pointsNiveauSuivant()
	{
		return (FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirPointsCampagne());
	}

	////////////////////////////////////////////////////////////////////////
	/// @fn	__declspec(dllexport) void __cdecl assignerifficulte(int point)
	///
	/// Cette fonction permet d'assigner les points du butoire Cible
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl assignerDifficulte(int point)
	{
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->assignerDifficulte(point);
	}

	////////////////////////////////////////////////////////////////////////
	/// @fn	__declspec(dllexport) bool __cdecl assignerJoueurVirtuel(bool estJoueurVirtuel);
	///
	/// Cette fonction permet d'activer/deactiver le le joueur virtuel
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl assignerJoueurVirtuel(bool estJoueurVirtuel)
	{
		FacadeModele::obtenirInstance()->assignerJoueurVirtuel(estJoueurVirtuel);
	}
	

	////////////////////////////////////////////////////////////////////////
	/// @fn		__declspec(dllexport) int __cdecl gameOver()
	///
	/// Cette fonctionne permet de savoir si le joueur a epuisee ses vies
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl gameOver()
	{
		return (FacadeModele::obtenirInstance()->obtenirBillesRestantes() == 0 && FacadeModele::obtenirInstance()->obtenirBillesEnJeu() == 0);
	}
	////////////////////////////////////////////////////////////////////////
	/// @fn	__declspec(dllexport) int __cdecl victoire()
	///
	/// Cette fonction permet de savoir si on a assez de points pour passer a lapartie suivante
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl victoire()
	{
		bool victoire = (FacadeModele::obtenirInstance()->obtenirPoints() >= FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirPointsCampagne());
		return false;
	}

	////////////////////////////////////////////////////////////////////////
	/// @fn	__declspec(dllexport) int __cdecl obtenirPointsButoireCirculaire(int point)
	///
	/// Cette fonction permet d'obtenir les points du butoire circulaire
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirPointsButoirCirculaire()
	{
		return FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirPointsButoirCir();
	}

	////////////////////////////////////////////////////////////////////////
	/// @fn	__declspec(dllexport) int __cdecl obtenirPointsButoireTriangulaire()
	///
	/// Cette fonction permet d'obtenir les points du butoire triangulaire
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirPointsButoirTriangulaire()
	{
		return FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirPointsButoirTri();
	}

	////////////////////////////////////////////////////////////////////////
	/// @fn	__declspec(dllexport) int __cdecl obtenirPointsCible(int point)
	///
	/// Cette fonction permet d'obtenir les points du butoire Cible
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirPointsCible()
	{
		return FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirPointsCible();
	}

	////////////////////////////////////////////////////////////////////////
	/// @fn	__declspec(dllexport) int __cdecl obtenirPointsNiveauSuivant()
	///
	/// Cette fonction permet d'obtenir les points pour passer au niveau suivant
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirPointsNiveauSuivant()
	{
		return FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirPointsCampagne();
	}

	////////////////////////////////////////////////////////////////////////
	/// @fn	__declspec(dllexport) int __cdecl obtenirPointsBilleBonus()
	///
	/// Cette fonction permet d'obtenir les points du butoire Cible
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirPointsBilleBonus()
	{
		return FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirPointsBille();
	}

	////////////////////////////////////////////////////////////////////////
	/// @fn	__declspec(dllexport) int __cdecl obtenirDifficulte(int point)
	///
	/// Cette fonction permet d'obtenir la difficulte du niveau
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirDifficulteProp()
	{
		return FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirDifficulte();
	}

	////////////////////////////////////////////////////////////////////////
	/// @fn __declspec(dllexport) void __cdecl activerSonBackground()
	///
	/// Cette fonction permet de demarrer le son de background
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl activerSonBackground()
	{
		FacadeModele::obtenirInstance()->obtenirSon()->initialiser();
	}

	////////////////////////////////////////////////////////////////////////
	/// @fn __declspec(dllexport) void __cdecl activerSonVictoire()
	///
	/// Cette fonction permet de demarrer le son de de victoire
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl activerSonVictoire()
	{
		FacadeModele::obtenirInstance()->obtenirSon()->sonWin();
	}
	////////////////////////////////////////////////////////////////////////
	/// @fn __declspec(dllexport) void __cdecl desactiverSon()
	///
	/// Cette fonction permet de demarrer le son de background
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl desactiverSon()
	{
		FacadeModele::obtenirInstance()->obtenirSon()->mute();
	}

	////////////////////////////////////////////////////////////////////////
	/// @fn __declspec(dllexport) void __cdecl pauserSon()
	///
	/// Cette fonction permet de demarrer le son de background
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl pauserSon()
	{
		FacadeModele::obtenirInstance()->obtenirSon()->pause();
	}

	////////////////////////////////////////////////////////////////////////
	/// @fn	__declspec(dllexport) int __cdecl obtenirDifficulte(int point)
	///
	/// Cette fonction permet de changer la vue à Ortho
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl changeToOrtho()
	{
		return FacadeModele::obtenirInstance()->changeToOrtho();
	}

	////////////////////////////////////////////////////////////////////////
	/// @fn	__declspec(dllexport) int __cdecl obtenirDifficulte(int point)
	///
	/// Cette fonction permet de changer la vue à Perspesctive
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl changeToPerspective()
	{
		return FacadeModele::obtenirInstance()->changeToPerspective();
	}

	////////////////////////////////////////////////////////////////////////
	/// @fn	__declspec(dllexport) int __cdecl changeLumAmbiant()
	///
	/// Cette fonction permet de changer la vue à Perspesctive
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl changeLumAmbiant()
	{
		return FacadeModele::obtenirInstance()->assignerLumAmbiante();
	}

	////////////////////////////////////////////////////////////////////////
	/// @fn	__declspec(dllexport) int __cdecl changeLumDirect()
	///
	/// Cette fonction permet d'activer la lumière directionnelle
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl changeLumDirect()
	{
		return FacadeModele::obtenirInstance()->assignerLumDirect();
	}

	////////////////////////////////////////////////////////////////////////
	/// @fn	__declspec(dllexport) int __cdecl changeLumSpot()
	///
	/// Cette fonction permet d'activer les projecteurs
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl changeLumSpot()
	{
		return FacadeModele::obtenirInstance()->assignerLumSpot();
	}

	////////////////////////////////////////////////////////////////////////
	/// @fn	__declspec(dllexport) void __cdecl affichageTexte(int point)
	///
	/// Cette fonction inverse la condition d'affichage de texte
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl affichageTexte()
	{
		FacadeModele::obtenirInstance()->inverserAffichageTexte();
	}
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////