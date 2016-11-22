///////////////////////////////////////////////////////////////////////////////
/// @file FacadeModele.cpp
/// @author Martin Bisson
/// @date 2007-05-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////


// Commentaire Doxygen mis sur la première page de la documentation Doxygen.
/**

@mainpage Projet intégrateur de deuxième année -- INF2990

*/

#include <windows.h>
#include <cassert>
#include <vector>
#include "GL/glew.h"
#include "FreeImage.h"

#include "FacadeModele.h"
#include "NoeudMur.h"
#include "NoeudPortail.h"

#include "VueOrtho.h"
#include "Camera.h"
#include "Projection.h"

#include "Utilitaire.h"
#include "AideGL.h"
#include "ArbreRenduINF2990.h"

#include "ConfigScene.h"
#include "CompteurAffichage.h"

#include "../Arbre/Visiteurs/VisiteurTranslation.h"
#include "../Arbre/Visiteurs/VisiteurRotation.h"
#include "../Arbre/Visiteurs/VisiteurScale.h"
#include "../Arbre/Visiteurs/VisiteurDuplication.h"

// Remlacement de EnveloppeXML/XercesC par TinyXML
// Julien Gascon-Samson, été 2011
#include "tinyxml.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

/// Pointeur vers l'instance unique de la classe.
FacadeModele* FacadeModele::instance_{ nullptr };

/// Chaîne indiquant le nom du fichier de configuration du projet.
const std::string FacadeModele::FICHIER_CONFIGURATION{ "configuration.xml" };


VisiteurTranslation* FacadeModele::visiteurTranslation = nullptr;
VisiteurLireXML* FacadeModele::visiteurLireXML = nullptr;
VisiteurEcrireXML* FacadeModele::visiteurEcrireXML = nullptr;
VisiteurMouvement* FacadeModele::visiteurMouvement_ = 0;


////////////////////////////////////////////////////////////////////////
///
/// @fn FacadeModele* FacadeModele::obtenirInstance()
///
/// Cette fonction retourne un pointeur vers l'instance unique de la
/// classe.  Si cette instance n'a pas été créée, elle la crée.  Cette
/// création n'est toutefois pas nécessairement "thread-safe", car
/// aucun verrou n'est pris entre le test pour savoir si l'instance
/// existe et le moment de sa création.
///
/// @return Un pointeur vers l'instance unique de cette classe.
///
////////////////////////////////////////////////////////////////////////
FacadeModele* FacadeModele::obtenirInstance()
{
	if (instance_ == nullptr)
		instance_ = new FacadeModele;

	return instance_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::libererInstance()
///
/// Cette fonction libère l'instance unique de cette classe.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::libererInstance()
{
	delete instance_;
	instance_ = nullptr;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn FacadeModele::~FacadeModele()
///
/// Ce destructeur libère les objets du modèle.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
FacadeModele::~FacadeModele()
{
	delete arbre_;
	delete vue_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::initialiserOpenGL(HWND hWnd)
///
/// Cette fonction permet d'initialiser le contexte OpenGL.  Elle crée
/// un contexte OpenGL sur la fenêtre passée en paramètre, initialise
/// FreeImage (utilisée par le chargeur de modèles) et assigne des 
/// paramètres du contexte OpenGL.
///
/// @param[in] hWnd : La poignée ("handle") vers la fenêtre à utiliser.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::initialiserOpenGL(HWND hWnd)
{
	hWnd_ = hWnd;
	bool succes{ aidegl::creerContexteGL(hWnd_, hDC_, hGLRC_) };
	assert(succes && "Le contexte OpenGL n'a pu être créé.");

	// Initialisation des extensions de OpenGL
	glewInit();

	// Initialisation de la configuration
	chargerConfiguration();

	// FreeImage, utilisée par le chargeur, doit être initialisée
	FreeImage_Initialise();

	// La couleur de fond
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Les lumières
	glEnable(GL_LIGHTING);
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glEnable(GL_COLOR_MATERIAL);
	/// Pour normaliser les normales dans le cas d'utilisation de glScale[fd]
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHT0);

	// Qualité
	glShadeModel(GL_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	// Profondeur
	glEnable(GL_DEPTH_TEST);

	// Le cull face
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);


	// Création de l'arbre de rendu.  À moins d'être complètement certain
	// d'avoir une bonne raison de faire autrement, il est plus sage de créer
	// l'arbre après avoir créé le contexte OpenGL.
	arbre_ = new ArbreRenduINF2990;
	arbre_->initialiser();

	// On crée une vue par défaut.
	vue_ = new vue::VueOrtho{
		vue::Camera{ 
			glm::dvec3(0, 0, 200), glm::dvec3(0, 0, 0),
			glm::dvec3(0, 1, 0),   glm::dvec3(0, 1, 0)},
		vue::ProjectionOrtho{ 
				0, 500, 0, 500,
				1, 1000, 1, 10000, 1.25,
				-100, 100, -100, 100 }
	};
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::chargerConfiguration() const
///
/// Cette fonction charge la configuration à partir d'un fichier XML si
/// ce dernier existe.  Sinon, le fichier de configuration est généré à
/// partir de valeurs par défaut directement dans le code.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::chargerConfiguration() const
{
	// Vérification de l'existance du ficher

	// Si le fichier n'existe pas, on le crée.
	if (!utilitaire::fichierExiste(FICHIER_CONFIGURATION)) {
		enregistrerConfiguration();
	}
	// si le fichier existe on le lit
	else {
		TiXmlDocument document;

		// Lire à partir du fichier de configuration
		document.LoadFile(FacadeModele::FICHIER_CONFIGURATION.c_str());

		// On lit les différentes configurations.
		ConfigScene::obtenirInstance()->lireDOM(document);
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::enregistrerConfiguration() const
///
/// Cette fonction génère un fichier XML de configuration à partir de
/// valeurs par défaut directement dans le code.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::enregistrerConfiguration() const
{
	TiXmlDocument document;

	// Écrire la déclaration XML standard...
	TiXmlDeclaration* declaration{ new TiXmlDeclaration{ "1.0", "", "" } };
	document.LinkEndChild(declaration);

	// On enregistre les différentes configurations.
	ConfigScene::obtenirInstance()->creerDOM(document);

	// Écrire dans le fichier
	document.SaveFile(FacadeModele::FICHIER_CONFIGURATION.c_str());
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::libererOpenGL()
///
/// Cette fonction libère le contexte OpenGL et désinitialise FreeImage.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::libererOpenGL()
{
	utilitaire::CompteurAffichage::libererInstance();

	// On libère les instances des différentes configurations.
	ConfigScene::libererInstance();


	bool succes{ aidegl::detruireContexteGL(hWnd_, hDC_, hGLRC_) };
	assert(succes && "Le contexte OpenGL n'a pu être détruit.");

	FreeImage_DeInitialise();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::afficher() const
///
/// Cette fonction affiche le contenu de la scène.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::afficher() const
{
	// Efface l'ancien rendu
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Ne devrait pas être nécessaire
	vue_->appliquerProjection();

	// Positionne la caméra
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	vue_->appliquerCamera();

	// Afficher la scène
	afficherBase();

	// Compte de l'affichage
	utilitaire::CompteurAffichage::obtenirInstance()->signalerAffichage();

	// Échange les tampons pour que le résultat du rendu soit visible.
	::SwapBuffers(hDC_);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::afficherBase() const
///
/// Cette fonction affiche la base du contenu de la scène, c'est-à-dire
/// qu'elle met en place l'éclairage et affiche les objets.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::afficherBase() const
{
	// Positionner la lumière.
	glm::vec4 position{ 0, 0, 1, 0 };
	glLightfv(GL_LIGHT0, GL_POSITION, glm::value_ptr(position));

	// Afficher la scène.
	arbre_->afficher();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::reinitialiser()
///
/// Cette fonction réinitialise la scène à un état "vide".
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::reinitialiser()
{
	// Réinitialisation de la scène.
	arbre_->initialiser();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::animer(float temps)
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
void FacadeModele::animer(float temps)
{
	// Mise à jour des objets.
	arbre_->animer(temps);

	// Mise à jour de la vue.
	vue_->animer(temps);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::ajouterNoeud(std::string nom, glm::dvec3& point)
///
/// Cette fonction ajoute un noeud a l'arbre de rendu et modifie sa position relative selon l'endroi 
///
/// @param[in] nom : nom du type d'objet a créé
///
/// @param[in] point : emplacement virtuel correspondent au click
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::ajouterNoeud(std::string nom, glm::dvec3& point)
{
	arbre_->ajouterNouveauNoeud("plaque", nom)->assignerPositionRelative(point);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::ajouterNoeudMur(glm::dvec3& point1,glm::dvec3& point2)
///
/// Cette fonction ajoute un noeud mur a l'arbre de rendu et modifie sa position relative selon l'endroi 
///
/// @param[in] point1 : emplacement virtuel correspondent au click
///
/// @param[in] point2 : emplacement virtuel correspondent au click
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::ajouterNoeudMur(glm::dvec3& point1, glm::dvec3& point2)
{
	NoeudAbstrait* murAbstrait = arbre_->ajouterNouveauNoeud("plaque", "mur");
	NoeudMur* mur = dynamic_cast<NoeudMur*>(murAbstrait);
	
	glm::dvec3 centre = glm::dvec3();

	centre.x = (point1.x + point2.x) / 2;
	centre.y = (point1.y + point2.y) / 2;

	mur->assignerPositionRelative(centre);

	float distance = std::sqrt(((point1.x - point2.x)*(point1.x - point2.x)) + ((point1.y - point2.y)*(point1.y - point2.y)));

	mur->assignerScale(distance, 1, 1);

	float radian1 = (point2.y - point1.y);
	float radian2 = (point2.x - point1.x);
	float radian = radian1 / radian2;
	float angle = std::atan(radian);
	float angleDeg = ((angle * 180) / 3.141592);

	mur->assignerAngleRotation(angleDeg);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::ajouterNoeudPortail(glm::dvec3& point1,glm::dvec3& point2)
///
/// Cette fonction ajoute deux noeuds portail a l'arbre de rendu et modifie sa position relative selon l'endroi 
///
/// @param[in] point1 : emplacement virtuel correspondent au click 1
///
/// @param[in] point2 : emplacement virtuel correspondent au click 1
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::ajouterNoeudPortail(glm::dvec3& point1, glm::dvec3& point2)
{
	int portailId = arbre_->obtenirIdPortail();
	NoeudAbstrait* portailAbstrait1 = arbre_->ajouterNouveauNoeud("plaque", "portail");
	NoeudPortail* portail1 = dynamic_cast<NoeudPortail*>(portailAbstrait1);
	portail1->assignerId(portailId);

	NoeudAbstrait* portailAbstrait2 = arbre_->ajouterNouveauNoeud("plaque", "portail");
	NoeudPortail* portail2 = dynamic_cast<NoeudPortail*>(portailAbstrait2);
	portail2->assignerId(portailId);

	portail1->assignerPositionRelative(point1);
	portail2->assignerPositionRelative(point2);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn    void selectionSimple(int x, int y)
///
/// Cette fonction ajoute un noeud a l'arbre de rendu et modifie sa position relative selon l'endroi 
///
/// @param[in] x : position en x de l'objet recherché
///
/// @param[in] y : position en y del'objet recherché
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////

void FacadeModele::selectionSimple(glm::dvec3 point)
{
	std::vector<NoeudAbstrait*> avisiter = std::vector<NoeudAbstrait*>();
	avisiter.push_back(arbre_);
	while (!avisiter.empty())
	{
		NoeudAbstrait* noeud = avisiter.back();
		avisiter.pop_back();

		if (noeud->estSelectionnable())
		{
			BoiteEnglobante boite = noeud->obtenirBoiteEnglobante();

			if (utilitaire::DANS_LIMITESXY(point[0],   boite.coinBG[0], boite.coinBD[0], point[1], boite.coinBG[1], boite.coinHG[1]))
			{
				noeud->inverserSelection();
			}

		}

		for (int i = 0; i < noeud->obtenirNombreEnfants(); i++)
		{
			avisiter.push_back(noeud->chercher(i));
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn    void FacadeModele::selectionMultiple(glm::dvec3 min, glm::dvec3 max)
///
/// Cette fonction ajoute un noeud a l'arbre de rendu et modifie sa position relative selon l'endroi 
///
/// @param[in] min,max : sommet dela boite dans laquelle on sélectionne les objets
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::selectionMultiple(glm::dvec3 min, glm::dvec3 max)
{
	std::vector<NoeudAbstrait*> avisiter = std::vector<NoeudAbstrait*>();
	avisiter.push_back(arbre_);
	while (!avisiter.empty())
	{
		NoeudAbstrait* noeud = avisiter.back();
		avisiter.pop_back();

		if (noeud->estSelectionnable())
		{
			BoiteEnglobante boite = noeud->obtenirBoiteEnglobante();

			if (utilitaire::DANS_LIMITESXY(boite.coinBG[0], min[0], max[0], boite.coinBG[1], min[1], max[1])
				|| utilitaire::DANS_LIMITESXY(boite.coinHG[0], min[0], max[0], boite.coinHG[1], min[1], max[1])
				|| utilitaire::DANS_LIMITESXY(boite.coinBD[0], min[0], max[0], boite.coinBD[1], min[1], max[1])
				|| utilitaire::DANS_LIMITESXY(boite.coinHD[0], min[0], max[0], boite.coinHD[1], min[1], max[1]))
			{
				noeud->inverserSelection();
			}
		}

		for (int i = 0; i < noeud->obtenirNombreEnfants(); i++)
		{
			avisiter.push_back(noeud->chercher(i));
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::translation(glm::dvec3 point)
///
/// Cette fonction effectue une translation sur tout les noeuds selectionner
///
/// @param[in] point : point de translation
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::translation(glm::dvec3 point)
{
	std::vector<NoeudAbstrait*> noeudSelectionnes = arbre_->obtenirNoeudSelectionnes();

	glm::dvec3 centre = obtenirPointCentral(noeudSelectionnes);

	if (visiteurMouvement_ == nullptr || visiteurMouvement_->getType() != "TRANSLATION")
	{
		visiteurMouvement_ = new VisiteurTranslation(noeudSelectionnes);
	}

	visiteurMouvement_->visiteAll(point);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::translationSouris(glm::dvec3 point)
///
/// Cette fonction effectue une translation sur tout les noeuds selectionner
///
/// @param[in] point : point de translation
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::translationSouris(glm::dvec3 point)
{
	std::vector<NoeudAbstrait*> noeudSelectionnes = std::vector<NoeudAbstrait*>();
	noeudSelectionnes.push_back(arbre_->chercher("plaque"));

	glm::dvec3 centre = obtenirPointCentral(noeudSelectionnes);

	if (visiteurMouvement_ == nullptr || visiteurMouvement_->getType() != "TRANSLATION")
	{
		visiteurMouvement_ = new VisiteurTranslation(noeudSelectionnes);
	}

	visiteurMouvement_->visiteAll(point);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::miseEchelle(double scale)
///
/// Cette fonction effectue une mise a lechelle sur le noeud selectionner
///
/// @param[in] scale : valeur delamise a lechelle
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::miseEchelle(double scale)
{
	std::vector<NoeudAbstrait*> vectNoeud = arbre_->obtenirNoeudSelectionnes();
	NoeudAbstrait* noeud = *(vectNoeud.begin());
	noeud->assignerMultiplicateurScale(scale);
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::validateMouvement(std::vector<NoeudAbstrait*> noeuds)
///
/// Cette fonction valide un mouvement de noued
///
/// @param[in] noeuds : noueds modifies
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::validateMouvement()
{
	std::vector<NoeudAbstrait*> noeuds = arbre_->obtenirNoeudSelectionnes();
	boolean isValid = true;
	if (visiteurMouvement_ != nullptr && visiteurMouvement_->getType() == "DUPLICATION")
		noeuds = ((VisiteurDuplication*)visiteurMouvement_)->getCopies();
	BoiteEnglobante surfaceDeJeu = arbre_->chercher(0)->obtenirBoiteEnglobante();
	for each(NoeudAbstrait* noeud in noeuds)
	{
		BoiteEnglobante boite = noeud->obtenirBoiteEnglobante();
		while (!(utilitaire::DANS_LIMITESXY(boite.coinBD.x, surfaceDeJeu.coinBG.x, surfaceDeJeu.coinBD.x, boite.coinBD.y, surfaceDeJeu.coinBG.y, surfaceDeJeu.coinHD.y)
			&& utilitaire::DANS_LIMITESXY(boite.coinBG.x, surfaceDeJeu.coinBG.x, surfaceDeJeu.coinBD.x, boite.coinBG.y, surfaceDeJeu.coinBG.y, surfaceDeJeu.coinHD.y)
			&& utilitaire::DANS_LIMITESXY(boite.coinHD.x, surfaceDeJeu.coinBG.x, surfaceDeJeu.coinBD.x, boite.coinHD.y, surfaceDeJeu.coinBG.y, surfaceDeJeu.coinHD.y)
			&& utilitaire::DANS_LIMITESXY(boite.coinHG.x, surfaceDeJeu.coinBG.x, surfaceDeJeu.coinBD.x, boite.coinHG.y, surfaceDeJeu.coinBG.y, surfaceDeJeu.coinHD.y))
			&& isValid)
		{
			if (visiteurMouvement_ != nullptr && visiteurMouvement_->getType() == "DUPLICATION")
				isValid = false;
			else
			{
				revertMouvement();
				boite = noeud->obtenirBoiteEnglobante();
			}
		}
	}
	if (visiteurMouvement_ != nullptr && visiteurMouvement_->getType() == "DUPLICATION" && !isValid)
	{
		for each(NoeudAbstrait* noeud in noeuds)
		{
			noeud->obtenirParent()->effacer(noeud);
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::revertMouvement()
///
/// Cette fonction renverse une translation sur tout les noeuds selectionner
///
/// @param[in] point : point de translation
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::revertMouvement()
{
	if (visiteurMouvement_ != nullptr)
	{
		visiteurMouvement_->revert();
	}
}

////////////////////////////////////////////////////////////////////////
/// @fn void FacadeModele::releaseVisiteur()
///
/// Cette fonction libere le Visiteur
///
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::releaseVisiteurs()
{
	if (visiteurMouvement_ != nullptr)
	{
		visiteurMouvement_ = nullptr;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn glm::dvec3 FacadeModele::obtenirPointCentral(std::vector<NoeudAbstrait*> noeudSelectionnes)
///
/// Cette fonction retourne le point central d' un goupede noeuds
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
glm::dvec3 FacadeModele::obtenirPointCentral(std::vector<NoeudAbstrait*> noeudSelectionnes)
{
	glm::dvec3 center = glm::dvec3();

	if (noeudSelectionnes.size() == 1)
		center = noeudSelectionnes.front()->obtenirPositionRelative();
	else
	{
		float maxX = noeudSelectionnes.front()->obtenirPositionRelative().x;
		float minX = noeudSelectionnes.front()->obtenirPositionRelative().x;
		float maxY = noeudSelectionnes.front()->obtenirPositionRelative().y;
		float minY = noeudSelectionnes.front()->obtenirPositionRelative().y;

		for each(NoeudAbstrait* noeud in noeudSelectionnes)
		{
			if (noeud->obtenirPositionRelative().x > maxX)
				maxX = noeud->obtenirPositionRelative().x;
			if (noeud->obtenirPositionRelative().x < minX)
				minX = noeud->obtenirPositionRelative().x;

			if (noeud->obtenirPositionRelative().y > maxY)
				maxY = noeud->obtenirPositionRelative().y;
			if (noeud->obtenirPositionRelative().y < minY)
				minY = noeud->obtenirPositionRelative().y;
		}
		center.x = (maxX + minX) / 2;
		center.y = (maxY + minY) / 2;
	}
	return center;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::rotation(double angle)
///
/// Cette fonction effectue une rotation sur tout les noeuds selectionner
///
/// @param[in] angle : angle de la rotation
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::rotation(double angle)
{
	std::vector<NoeudAbstrait*> noeudSelectionnes = arbre_->obtenirNoeudSelectionnes();

	glm::dvec3 centre = obtenirPointCentral(noeudSelectionnes);

	if (visiteurMouvement_ == nullptr || visiteurMouvement_->getType() != "ROTATION")
	{
		visiteurMouvement_ = new VisiteurRotation(centre, noeudSelectionnes);
	}

	glm::dvec3 vectAngle = glm::dvec3();
	vectAngle[0] = angle;

	visiteurMouvement_->visiteAll(vectAngle);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::scale(glm::dvec3 point)
///
/// Cette fonction effectue une mise à l'échelle sur les objets de la scene
///
/// @param[in] point : point qui représente la position de la souris
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::scale(glm::dvec3 point)
{
	std::vector<NoeudAbstrait*> noeudSelectionnes = arbre_->obtenirNoeudSelectionnes();

	if (visiteurMouvement_ == nullptr || visiteurMouvement_->getType() != "SCALE")
	{
		visiteurMouvement_ = new VisiteurScale(point, noeudSelectionnes);
	}

	visiteurMouvement_->visiteAll(point);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::duplication(glm::dvec3 point)
///
/// Cette fonction effectue une duplication des objets selectionnés
///
/// @param[in] point : point qui représente la position de la souris
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::duplication(glm::dvec3 point)
{
	std::vector<NoeudAbstrait*> noeudSelectionnes = arbre_->obtenirNoeudSelectionnes();

	glm::dvec3 centre = obtenirPointCentral(noeudSelectionnes);

	if (visiteurMouvement_ == nullptr || visiteurMouvement_->getType() != "DUPLICATION")
	{
		visiteurMouvement_ = new VisiteurDuplication(arbre_, centre, noeudSelectionnes);
	}

	visiteurMouvement_->visiteAll(point);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool FacadeModele::sauvegardeArbreXML()
///
/// Cette fonction sauvegarde le jeu sous format XML
///
/// @param[in] string : le nom du fichier pour la sauvegarde
///
/// @return bool : facteur de sécurité (à venir)
///
////////////////////////////////////////////////////////////////////////
bool FacadeModele::sauvegardeArbreXML(std::string nomFichier)
{
	if (visiteurEcrireXML == nullptr)
		visiteurEcrireXML = new VisiteurEcrireXML();

	visiteurEcrireXML->initialiseXML();
	visiteurEcrireXML->ecritureXML(arbre_);
	visiteurEcrireXML->sauvegardeXML(nomFichier);

	return true;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool FacadeModele::supprimer()
///
/// Cette fonction supprime les objets sélectionnées de la scene
///
/// @param[in] Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::supprimer()
{
	arbre_->effacerSelection();
}

/// TODO
/// @fn bool FacadeModele::sauvegardePossible()
///
/// Cette fonction sauvegarde le jeu sous format XML
///
/// @param[in] string : le nom du fichier pour la sauvegarde
///
/// @return bool : facteur de sécurité
///
////////////////////////////////////////////////////////////////////////
bool FacadeModele::sauvegardePossible()
{
	bool trouTrouver = false;
	bool generateurTrouver = false;
	bool ressortTrouver = false;
	
	std::vector<NoeudAbstrait*> avisiter = std::vector<NoeudAbstrait*>();
	avisiter.push_back(arbre_);
	while (!avisiter.empty())
	{
		NoeudAbstrait* noeud = avisiter.back();
		avisiter.pop_back();

		std::string type = noeud->obtenirType();

		if (type == "trou")
			trouTrouver = true;
		else if(type == "generateurBille")
			generateurTrouver = true;
		else if (type == "ressort")
			ressortTrouver = true;
		
		for (int i = 0; i < noeud->obtenirNombreEnfants(); i++)
		{
			avisiter.push_back(noeud->chercher(i));
		}
	}
	
	if (trouTrouver && generateurTrouver && ressortTrouver)
		return true;
	else
		return false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool FacadeModele::lectureXML(std::string nomFichier)
///
/// Cette fonction sauvegarde le jeu sous format XML
///
/// @param[in] string : le nom du fichier pour la sauvegarde
///
/// @return bool : facteur de sécurité (à venir)
///
////////////////////////////////////////////////////////////////////////
bool FacadeModele::lectureXML(char* nomFichier)
{
	/// Démarre le visiteur lire XML
	if (visiteurLireXML == nullptr)
	{
		visiteurLireXML = new VisiteurLireXML();
		visiteurLireXML->assignerPointeurArbre(arbre_);
	}

	/// on ouvre le fichier
	if (visiteurLireXML->ouvrirXML(nomFichier))
	{
		if (visiteurLireXML->verifieXML())
		{
			arbre_->vider();
			return visiteurLireXML->parcourirXML();
		}
		else
			return false;
	}
	else
		return false;
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
