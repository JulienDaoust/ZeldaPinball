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
	__declspec(dllexport) int obtenirAffichagesParSeconde();
	__declspec(dllexport) bool executerTests();
	__declspec(dllexport) void __cdecl ajouterNoeud(char* nom, int x, int y);
	__declspec(dllexport) void __cdecl selectionSimple(int x, int y);
	__declspec(dllexport) void __cdecl selectionMultiple(int gauche, int haut, int droite, int bas);
	__declspec(dllexport) void __cdecl deselectionnerTout();
	__declspec(dllexport) void __cdecl RetournerPosition(int x, int y);

}

#endif // __FACADE_INTERFACE_NATIVE_H__
