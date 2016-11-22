//////////////////////////////////////////////////////////////////////////////
/// @file QuadTree.h
/// @author Loic sauvageau
/// @date 2005-06-15
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __QUADTREE_H__
#define __QUADTREE_H__

#include <vector>
#include "../Arbre/Noeuds/NoeudAbstrait.h"
#include <iostream>


class QuadTree
{
public:
	QuadTree(int niveau, glm::dvec3 coinHG, glm::dvec3 coinBG, glm::dvec3 coinHD, glm::dvec3 coinBD);
	~QuadTree();

	/// méthode pour vider l'arbre
	void vider();

	/// méthode pour insérer un noeud
	void ajoutNoeud(NoeudAbstrait* noeud);

	/// méthode pour diviser la surface en quatre
	void subdiviser();

	/// obtenir l'index lors de l'insertion dans les sous quad
	int obtenirIndex(NoeudAbstrait* noeud);

	/// obtenir les objets en collision
	void obtenirListeCollision(std::vector<NoeudAbstrait*> &liste, NoeudAbstrait* noeud);


private:

	const int TAILLE_MAX = 4;
	const int NIVEAU_MAX = 5;

	double miHauteur = 0;
	double miLargeur = 0;

	int niveau;
	std::vector<NoeudAbstrait*> listeNoeud;
	BoiteEnglobante surface;
	QuadTree* quartier[4];
};




#endif // !__QUADTREE_H__
