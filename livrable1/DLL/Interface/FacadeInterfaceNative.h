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
}

#endif // __FACADE_INTERFACE_NATIVE_H__
