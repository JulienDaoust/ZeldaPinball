////////////////////////////////////////////////
/// @file   FacadeInterfaceNative.h
/// @author INF2990
/// @date   2014-08-16
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////
#include <string>
#ifndef __FACADE_INTERFACE_NATIVE_H__
#define __FACADE_INTERFACE_NATIVE_H__

extern "C" {

	__declspec(dllexport) void initialiserOpenGL(int * handle);
	__declspec(dllexport) void libererOpenGL();
	__declspec(dllexport) void dessinerOpenGL();
	__declspec(dllexport) void redimensionnerFenetre(int largeur, int hauteur);
	__declspec(dllexport) void animer(double temps);
	__declspec(dllexport) void zoomIn();
	__declspec(dllexport) void zoomOut();
	__declspec(dllexport) void __cdecl ZoomOutRectangle(int minX, int minY, int maxX, int maxY);
	__declspec(dllexport) void __cdecl ZoomInRectangle(int minX, int minY, int maxX, int maxY);
	__declspec(dllexport) int obtenirAffichagesParSeconde();
	__declspec(dllexport) bool executerTests();
	__declspec(dllexport) void __cdecl ajouterNoeud(char* nom, int x, int y);
	__declspec(dllexport) void __cdecl ajouterNoeudMur(int x1, int y1, int x2, int y2);
	__declspec(dllexport) void __cdecl ajouterNoeudPortail(int x1, int y1, int x2, int y2);
	__declspec(dllexport) void __cdecl selectionSimple(int x, int y);
	__declspec(dllexport) void __cdecl selectionMultiple(int gauche, int haut, int droite, int bas);
	__declspec(dllexport) void __cdecl deselectionnerTout();
	__declspec(dllexport) void __cdecl RetournerPosition(int x, int y);
	__declspec(dllexport) void __cdecl translation(int x1, int y1, int x2, int y2);
	__declspec(dllexport) void __cdecl translationX(int x);
	__declspec(dllexport) void __cdecl translationY(int y);
	__declspec(dllexport) void __cdecl translationSouris(int x1, int y1, int x2, int y2);
	__declspec(dllexport) void __cdecl validateMouvement();
	__declspec(dllexport) void __cdecl releaseVisiteurs();
	__declspec(dllexport) void __cdecl rotation(double angle);
	__declspec(dllexport) void __cdecl miseEchelle(double scale);
	__declspec(dllexport) void __cdecl rotationSimple(double angle);
	__declspec(dllexport) bool __cdecl ecritureXML(char* nom);
	__declspec(dllexport) bool __cdecl estSauvegardable();
	__declspec(dllexport) bool __cdecl lireXML(char* nom);
	__declspec(dllexport) void __cdecl scaling(int x, int y);
	__declspec(dllexport) void __cdecl duplication(int x, int y);
	__declspec(dllexport) void __cdecl supprimerObjets();
	__declspec(dllexport) int __cdecl estSelectionne();
	__declspec(dllexport) void __cdecl changerPoints(int points, char* nom);
	__declspec(dllexport) void __cdecl changerDifficulte(int points);
	__declspec(dllexport) void __cdecl changerPointsCampagne(int points);
	__declspec(dllexport) void __cdecl changerPointsBille(int points);
	__declspec(dllexport) void __cdecl reinitialiser();

	__declspec(dllexport) void __cdecl assignerPointsButoirCirculaire(int point);
	__declspec(dllexport) void __cdecl assignerPointsButoirTriangulaire(int point);
	__declspec(dllexport) void __cdecl assignerPointsCible(int point);
	__declspec(dllexport) void __cdecl assignerPointsNiveauSuivant(int point);
	__declspec(dllexport) void __cdecl assignerPointsBilleBonus(int point);
	
	__declspec(dllexport) void __cdecl assignerDifficulte(int difficulte);

	__declspec(dllexport) int __cdecl obtenirPointsButoirCirculaire();
	__declspec(dllexport) int __cdecl obtenirPointsButoirTriangulaire();
	__declspec(dllexport) int __cdecl obtenirPointsCible();
	__declspec(dllexport) int __cdecl obtenirPointsBilleBonus();
	__declspec(dllexport) int __cdecl obtenirDifficulteProp();

	__declspec(dllexport) int __cdecl obtenirPointsNiveauSuivant();
	__declspec(dllexport) int __cdecl obtenirDifficulte(char* nomFichier);
	__declspec(dllexport) void __cdecl assignerNbBillesInitial(int nbBilles);
	__declspec(dllexport) int __cdecl obtenirNbBillesActuel();
	__declspec(dllexport) int __cdecl obtenirPointageActuel();


	__declspec(dllexport) void __cdecl animerPaletteGJ1(bool sound);
	__declspec(dllexport) void __cdecl animerPaletteDJ1(bool sound);
	__declspec(dllexport) void __cdecl animerPaletteGJ2(bool sound);
	__declspec(dllexport) void __cdecl animerPaletteDJ2(bool sound);
	__declspec(dllexport) void __cdecl reinitialiserPartie();
	__declspec(dllexport) void __cdecl assignerDebug(bool* dbug);
	__declspec(dllexport) void __cdecl animerRessort(bool animer);

	__declspec(dllexport) void __cdecl assignerBillesRestantes(int billes);
	__declspec(dllexport) void __cdecl assignerBillesMax(int billes);
	__declspec(dllexport) void __cdecl assignerAffichageDebug(bool affiche);
	__declspec(dllexport) void __cdecl assignerAffichageVitesse(bool affiche);
	__declspec(dllexport) void __cdecl assignerAffichageCreationBille(bool affiche);
	__declspec(dllexport) void __cdecl assignerAffichagePortail(bool affiche);
	
	__declspec(dllexport) void __cdecl assignerJoueurVirtuel(bool estJoueurVirtuel);

	__declspec(dllexport) int __cdecl gameOver();
	__declspec(dllexport) int __cdecl victoire();

	__declspec(dllexport) void __cdecl activerSonBackground();
	__declspec(dllexport) void __cdecl activerSonVictoire();
	__declspec(dllexport) void __cdecl desactiverSon();
	__declspec(dllexport) void __cdecl pauserSon();

	__declspec(dllexport) void __cdecl changeToOrtho();
	__declspec(dllexport) void __cdecl changeToPerspective();

	__declspec(dllexport) void __cdecl changeLumAmbiant();
	__declspec(dllexport) void __cdecl changeLumDirect();
	__declspec(dllexport) void __cdecl changeLumSpot();
	__declspec(dllexport) void __cdecl affichageTexte();
}

#endif // __FACADE_INTERFACE_NATIVE_H__
