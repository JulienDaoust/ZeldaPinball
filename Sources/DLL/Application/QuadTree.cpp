#include "QuadTree.h"
#include <algorithm>

/// Constructeur
QuadTree::QuadTree(int niveau, glm::dvec3 coinHG, glm::dvec3 coinBG, glm::dvec3 coinHD, glm::dvec3 coinBD)
{
	this->niveau = niveau;
	surface = { coinHG, coinBG, coinHD, coinBD };
	for (int i = 0; i < 4; ++i)
		quartier[i] = nullptr;

	miHauteur = surface.coinHD.y - (surface.coinHD.y - surface.coinBD.y) / 2;
	miLargeur = surface.coinHD.x - (surface.coinHD.x - surface.coinBG.x) / 2;

	listeNoeud = std::vector<NoeudAbstrait*>();
}

/// Destructeur
QuadTree::~QuadTree()
{
	vider();
}

/// méthode pour vider l'arbre
void QuadTree::vider()
{
	/// la liste des noeuds est vidée
	if (!(listeNoeud.empty()))
		listeNoeud.clear();

	/// on vide récursivement les quartiers
	if (quartier[0] != nullptr)
	{
		for (int i = 0; i < 4; ++i)
		{
			quartier[i]->vider();
			delete quartier[i];
			quartier[i] = nullptr;
		}
	}
}

/// méthode pour insérer un noeud
void QuadTree::ajoutNoeud(NoeudAbstrait * noeud)
{
	/// vérification si le noeud est déjà divisé
	if (quartier[0] != nullptr)
	{
		/// trouvé la position du noeud dans les enfants
		int indexNoeud = obtenirIndex(noeud);
		if (indexNoeud != -1)
		{
			quartier[indexNoeud]->ajoutNoeud(noeud);
			return;
		}
	}
	
	/// ajouter le noeud à la liste
	listeNoeud.push_back(noeud);

	/// vérification de la taille des quads
	if (listeNoeud.size() > TAILLE_MAX && niveau < NIVEAU_MAX)
	{
		if (quartier[0] == nullptr)
			subdiviser();

		/// héritage des noeuds du père à ses enfants
		int taille = 0;
		while (taille < listeNoeud.size())
		{
			/// trouvé la position du noeud dans les enfants
			int indexNoeud = obtenirIndex(listeNoeud[taille]);
			if (indexNoeud != -1)
			{
				quartier[indexNoeud]->ajoutNoeud(listeNoeud[taille]);
				listeNoeud.erase(listeNoeud.begin() + taille);
			}
			else
				taille++;
		}
	}
}

/// obtenir l'index lors de l'insertion dans les sous quad
int QuadTree::obtenirIndex(NoeudAbstrait* noeud)
{
	int index = -1;
	
	BoiteEnglobante boiteNoeud = noeud->obtenirBoiteEnglobante();

	double maxX = std::max(std::max(std::max(boiteNoeud.coinHG.x, boiteNoeud.coinHD.x), boiteNoeud.coinBG.x), boiteNoeud.coinBD.x);
	double maxY = std::max(std::max(std::max(boiteNoeud.coinHG.y, boiteNoeud.coinHD.y), boiteNoeud.coinBG.y), boiteNoeud.coinBD.y);

	double minX = std::min(std::min(std::min(boiteNoeud.coinHG.x, boiteNoeud.coinHD.x), boiteNoeud.coinBG.x), boiteNoeud.coinBD.x);
	double minY = std::min(std::min(std::min(boiteNoeud.coinHG.y, boiteNoeud.coinHD.y), boiteNoeud.coinBG.y), boiteNoeud.coinBD.y);

	/// la pièce peut complètement rentrer dans le quadrant haut
	bool quadrantHaut = (maxY > miHauteur && minY > miHauteur);

	/// la pièce peut complètement rentrer dans le quadrant bas
	bool quadrantBas = (maxY < miHauteur && minY < miHauteur);

	//la pièce est complètement dans le quadrant gauche
	if (minX > miLargeur && maxX > miLargeur)
	{
		if (quadrantHaut)
			index = 1;
		else if (quadrantBas)
			index = 2;
	}
	//la pièce est complètement dans le quadrant droit
	else if (minX < miLargeur && maxX < miLargeur)
	{
		if (quadrantHaut)
			index = 0;
		else if (quadrantBas)
			index = 3;
	}
	return index;
}

/// méthode pour diviser la surface en quatre
void QuadTree::subdiviser()
{
	/// création des coins
	double miHauteur = surface.coinHD.y - surface.coinBD.y;
	double miLargeur = surface.coinHD.x - surface.coinBG.x;
	glm::dvec3 miGauche{ surface.coinBG.x, miHauteur, 0 };
	glm::dvec3 miDroit{ surface.coinBD.x, miHauteur, 0 };
	glm::dvec3 miBas{ miLargeur, surface.coinBD.y, 0 };
	glm::dvec3 miHaut{ miLargeur, surface.coinHD.y, 0 };
	glm::dvec3 milieu{ miLargeur, miHauteur, 0 };

	/// création des nouveaux QuadTree
	quartier[0] = new QuadTree(niveau + 1, surface.coinHG, miGauche, miHaut, milieu); // haut gauche
	quartier[1] = new QuadTree(niveau + 1, miHaut, milieu, surface.coinHD, miDroit); // haut droit
	quartier[2] = new QuadTree(niveau + 1, milieu, miBas, miDroit, surface.coinBD); // bas droit
	quartier[3] = new QuadTree(niveau + 1, miGauche, surface.coinBG, milieu, miBas); //bas gauche
}


/// obtenir les objets en collision
void QuadTree::obtenirListeCollision(std::vector<NoeudAbstrait*> &liste, NoeudAbstrait* noeud)
{
	int index = obtenirIndex(noeud);

	if (index != -1 && quartier[0] != nullptr)
		quartier[index]->obtenirListeCollision(liste, noeud);

	for (int i = 0; i < listeNoeud.size(); i++)
		liste.push_back(listeNoeud[i]);

	return;
}
