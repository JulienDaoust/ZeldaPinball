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
#include "NoeudCible.h"

#include "VueOrtho.h"
#include "VuePerspective.h"
#include "Camera.h"
#include "Projection.h"

#include "Utilitaire.h"
#include "AideGL.h"
#include "ArbreRenduINF2990.h"

#include "ConfigScene.h"
#include "CompteurAffichage.h"
#include <ctime>

#include "../Arbre/Visiteurs/VisiteurTranslation.h"
#include "../Arbre/Visiteurs/VisiteurRotation.h"
#include "../Arbre/Visiteurs/VisiteurScale.h"
#include "../Arbre/Visiteurs/VisiteurDuplication.h"

// Remlacement de EnveloppeXML/XercesC par TinyXML
// Julien Gascon-Samson, été 2011
#include "tinyxml.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <iostream>

/// Pointeur vers l'instance unique de la classe.
FacadeModele* FacadeModele::instance_{ nullptr };

/// Chaîne indiquant le nom du fichier de configuration du projet.
const std::string FacadeModele::FICHIER_CONFIGURATION{ "../données/configuration.xml" };

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
	delete son_;
	delete visiteurCollision_;
	delete visiteurEcrireXML;
	delete visiteurLireXML;
	delete visiteurMouvement_;
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
	myfontPoints = new FTTextureFont("KGBlankSpaceSolid.ttf");
	myfontBille = new FTTextureFont("KGBlankSpaceSolid.ttf");

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
	
		
	//glEnable(GL_COLOR_MATERIAL);
	/// Pour normaliser les normales dans le cas d'utilisation de glScale[fd]
	glEnable(GL_NORMALIZE);

	// lumière directionnelle
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);

	glm::vec4 position{ 1, 1, 1, 0 };

	GLfloat spotPosition[] = { 1.0f, 0.f, 0.5f, 0.0f };
	GLfloat spotDirection[] = { -1.0f, 0.f, -0.5f, 0.0f };
	GLfloat lumiAmbiant0[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat lumiDiffuse0[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat lumiAmbiant1[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat lumiDiffuse1[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat lumiSpeculaire1[] = { 1.0, 1.0, 1.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_POSITION, spotPosition);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDirection);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lumiAmbiant0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lumiDiffuse0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lumiSpeculaire1);

	glLightfv(GL_LIGHT1, GL_AMBIENT, lumiAmbiant1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lumiDiffuse1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, lumiSpeculaire1);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30.0);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 1.0);

	glLightfv(GL_LIGHT2, GL_AMBIENT, lumiAmbiant1);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, lumiDiffuse1);
	glLightfv(GL_LIGHT2, GL_SPECULAR, lumiSpeculaire1);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 30.0);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 1.0);

	//// Appliquer le matéria
	//GLfloat mat_ambiant_modele[] = { 1.0, 1.0, 1.0, 1.0 };
	//GLfloat mat_diffuse_modele[] = { 1.0, 1.0, 1.0, 1.0 };
	//GLfloat mat_specular_modele[] = { 1.0, 1.0, 1.0, 1.0 };
	//GLfloat mat_emission_modele[] = { 0.0, 0.0, 0.0, 1.0 };
	//GLfloat mat_shininess_modele[] = { 100.0 };

	//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambiant_modele);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse_modele);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular_modele);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emission_modele);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess_modele);

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
	vue_ = new vue::VuePerspective{
		vue::Camera{
			glm::dvec3(0, 45, 100), glm::dvec3(0, 0, 0),
			glm::dvec3(0, 1, 0), glm::dvec3(0, 1, 0) },
			vue::ProjectionPerspective{
				0, 500, 0, 500,
				1, 1000, 100, 10000, 1.25,
				-0.8, 1, -0.8, 1 }
	};
	son_ = new Son();
	skybox_ = new utilitaire::BoiteEnvironnement("media/skybox/dunes_left.jpg", "media/skybox/dunes_right.jpg", "media/skybox/dunes_front.jpg", "media/skybox/dunes_back.jpg", "media/skybox/dunes_bottom.jpg", "media/skybox/dunes_top.jpg");
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

	skybox_->afficher(glm::dvec3(0,0,50), 500);
	// Afficher la scène
	afficherBase();
	if (peutAfficher)
	{
		// Affichage du texte pour les points
		afficherTextePoints();
		// Affichage du texte pour les billes
		afficherTexteBille();
	}
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
	
	// Controle de la lumière ambiante 
	if (!lumAmbiantActif)
	{
		GLfloat lmodel_ambiant[] = { 0.0, 0.0, 0.0, 1.0 };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambiant);
	}
	else
	{
		GLfloat lmodel_ambiant[] = { 0.5f, 0.5f, 0.5f, 1.0f };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambiant);
	}

	 // Controle de la lumière directionnelle (soleil)
	if (!lumDirectActif)
		glDisable(GL_LIGHT0);
	else
		glEnable(GL_LIGHT0);
	
	// On désactive initialement les projecteurs
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHT2);

	// Controle des projecteurs
	if (lumSpotActif)
	{
		// On obtient les noeuds billes présents
		std::vector<NoeudAbstrait*> vecBille;
		vecBille = arbre_->obtenirNoeudBille();

		int nombreBille = 0;
		NoeudAbstrait* noeud;
		glm::dvec3 positionNoeud;

		for (int i = 0; i < vecBille.size(); ++i)
		{
			if (nombreBille < 2)
			{
				noeud = vecBille[i];
				positionNoeud = noeud->obtenirPositionRelative();
				GLfloat spotPosition[] = { positionNoeud[0], positionNoeud[1], 15.0f, 1.0f };
				GLfloat spotDirection[] = { 0.0f, 0.0f, -1.0f };
				glLightfv(GL_LIGHT1 + nombreBille, GL_POSITION, spotPosition);
				glLightfv(GL_LIGHT1 + nombreBille, GL_SPOT_DIRECTION, spotDirection);
				glEnable(GL_LIGHT1 + nombreBille);
				++nombreBille;
			}
		}
	}

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
	arbre_->vider();
	libererInstance();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::reinitialiser()
///
/// Cette fonction change la vue en Ortho".
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::changeToOrtho()
{
	// Réinitialisation de la vue.
	vue_ = new vue::VueOrtho{
		vue::Camera{
			glm::dvec3(0, 0, 200), glm::dvec3(0, 0, 0),
			glm::dvec3(0, 1, 0), glm::dvec3(0, 1, 0) },
			vue::ProjectionOrtho{
				0, 500, 0, 500,
				1, 1000, 1, 10000, 1.25,
				-100, 100, -100, 100 }
	};
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::reinitialiser()
///
/// Cette fonction change la vue en Perspective".
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::changeToPerspective()
{
	// Réinitialisation de la vue.
	delete vue_;

	//Changement de vue
	vue_ = new vue::VuePerspective{
		vue::Camera{
			glm::dvec3(0, 45, 100), glm::dvec3(0, 0, 0),
			glm::dvec3(0, 1, 0), glm::dvec3(0, 1, 0) },
			vue::ProjectionPerspective{
				0, 500, 0, 500,
				1, 1000, 100, 10000, 1.25,
				-0.8, 1, -0.8, 1 }
	};

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
	if (visiteurCollision_ == nullptr)
		visiteurCollision_ = new VisiteurCollision();
	if (quadTree_ == nullptr)
	{
		BoiteEnglobante boite = arbre_->chercher(ArbreRenduINF2990::NOM_PLAQUE)->obtenirBoiteEnglobante();
		quadTree_ = new QuadTree(0, boite.coinHG, boite.coinBG, boite.coinHD, boite.coinBD);
	}
	else
	{
		quadTree_->vider();
	}

	NoeudAbstrait* table = arbre_->chercher(0);
	std::vector<NoeudAbstrait*> avisiter;

	quadTree_->ajoutNoeud(table);
	for (unsigned int i = 0; i < table->obtenirNombreEnfants(); i++)
	{
		NoeudAbstrait* noeud = table->chercher(i);
		quadTree_->ajoutNoeud(table->chercher(i));

		avisiter.push_back(table->chercher(i));
	}

	visiteurCollision_->dectectionCollision(avisiter);

	if (billesMax > billesEnJeu)
	{
		//si il y  a deja un billesur le jeu on attend en moyenne 5 sec pour en relacher une deuxieme

		if (billesEnJeu == 0 || compteurDeuxiemeBoule >= 60)
			creerBille();
		compteurDeuxiemeBoule++;
	}
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
	NoeudAbstrait* noeud = arbre_->ajouterNouveauNoeud("plaque", nom);
	noeud->assignerPositionRelative(point);
	if (nom == ArbreRenduINF2990::NOM_PORTAIL)
		((NoeudPortail*)noeud)->assignerDebug(affichageChampPortail);
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

	double distance = std::sqrt(((point1.x - point2.x)*(point1.x - point2.x)) + ((point1.y - point2.y)*(point1.y - point2.y)));

	mur->assignerScale(distance, 1, 1);

	double radian1 = (point2.y - point1.y);
	double radian2 = (point2.x - point1.x);
	double radian = radian1 / radian2;
	double angle = std::atan(radian);
	double angleDeg = ((angle * 180) / 3.141592);

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

			if (utilitaire::DANS_LIMITESXY(point[0], boite.coinBG[0], boite.coinBD[0], point[1], boite.coinBG[1], boite.coinHG[1]))
			{
				noeud->inverserSelection();
			}

		}

		for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++)
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

		for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++)
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
	if (noeudSelectionnes.size() > 0)
	{
		glm::dvec3 centre = obtenirPointCentral(noeudSelectionnes);

		if (visiteurMouvement_ == nullptr || visiteurMouvement_->getType() != "TRANSLATION")
		{
			visiteurMouvement_ = new VisiteurTranslation(noeudSelectionnes);
		}

		visiteurMouvement_->visiteAll(point);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::creerBille()
///
/// Cette fonction creer une bille a coter du generateur de bille
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::creerBille()
{
	if (billesRestantes != 0)
	{
		std::vector<NoeudAbstrait*> generateurs = arbre_->obtenirNoeudGenerateurBille();

		if (generateurs.size() > 0)
		{
			int index = rand() % generateurs.size();

			glm::dvec3 pos = generateurs[index]->obtenirPositionRelative();
			NoeudAbstrait* bille = arbre_->ajouterNouveauNoeud(ArbreRenduINF2990::NOM_PLAQUE, ArbreRenduINF2990::NOM_BILLE);
			bille->assignerPositionRelative(pos);
			billesEnJeu++;
			billesRestantes--;
			sortieConsoleCreationBille((NoeudBille*)bille);
			son_->sonBilleCreation();
		}

		compteurDeuxiemeBoule = 0;
	}
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
	if (noeud->estScaleable())
		noeud->assignerScale(scale, scale, scale);
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
///
/// @fn void FacadeModele::assignerBillesMax(int billes
///
/// Cette fonction assigne le nombre maximale de bille sur la table
///
/// @param[in] int : nombre de billemax
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::assignerBillesMax(int billes)
{
	billesMax = billes;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::decrementerBilleSurLaTable()
///
/// Cette fonction decremente le nombre de bille sur la table
///
/// @param[in] int : nombre de billemax
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::decrementerBilleSurLaTable()
{
	billesEnJeu--;
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
		delete visiteurMouvement_;
		visiteurMouvement_ = nullptr;
	}

	if (visiteurLireXML != nullptr)
	{
		visiteurLireXML = nullptr;
	}

	if (visiteurEcrireXML != nullptr)
	{
		visiteurEcrireXML = nullptr;
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
		double maxX = noeudSelectionnes.front()->obtenirPositionRelative().x;
		double minX = noeudSelectionnes.front()->obtenirPositionRelative().x;
		double maxY = noeudSelectionnes.front()->obtenirPositionRelative().y;
		double minY = noeudSelectionnes.front()->obtenirPositionRelative().y;

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
	if (noeudSelectionnes.size() > 0)
	{
		glm::dvec3 centre = obtenirPointCentral(noeudSelectionnes);

		if (visiteurMouvement_ == nullptr || visiteurMouvement_->getType() != "ROTATION")
		{
			visiteurMouvement_ = new VisiteurRotation(centre, noeudSelectionnes);
		}

		glm::dvec3 vectAngle = glm::dvec3();
		vectAngle[0] = angle;

		visiteurMouvement_->visiteAll(vectAngle);
	}
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
	if (noeudSelectionnes.size() > 0)
	{
		glm::dvec3 centre = obtenirPointCentral(noeudSelectionnes);

		if (visiteurMouvement_ == nullptr || visiteurMouvement_->getType() != "DUPLICATION")
		{
			visiteurMouvement_ = new VisiteurDuplication(arbre_, centre, noeudSelectionnes);
		}

		visiteurMouvement_->visiteAll(point);
	}
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
		else if (type == "generateurBille")
			generateurTrouver = true;
		else if (type == "ressort")
			ressortTrouver = true;

		for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++)
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
			bool value = visiteurLireXML->parcourirXML();
			if (value)
			{
				std::vector<NoeudAbstrait*>portails = arbre_->obtenirNoeudPortail();
				for each(NoeudAbstrait* portail in portails)
				{
					((NoeudPortail*)portail)->assignerDebug(affichageChampPortail&&affichageDebug);
				}
			}
			return value;
		}
		else
			return false;
	}
	else
		return false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn QuadTree* FacadeModele::obtenirQuadTree();
///
/// permet dé,acceder au quadtree
///
/// @return QuadTree* : pointeur sur le quadTree
///
////////////////////////////////////////////////////////////////////////
QuadTree* FacadeModele::obtenirQuadTree()
{
	return quadTree_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::reinitialiserPartie();
///
/// permet de reinitialiser la partie
///
/// @return none
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::reinitialiserPartie()
{
	std::vector<NoeudAbstrait*> avisiter = std::vector<NoeudAbstrait*>();
	avisiter.push_back(arbre_);
	while (!avisiter.empty())
	{
		NoeudAbstrait* noeud = avisiter.back();
		avisiter.pop_back();

		for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++)
		{
			avisiter.push_back(noeud->chercher(i));
		}

		if (noeud->obtenirType() == ArbreRenduINF2990::NOM_BILLE)
		{
			arbre_->effacer(noeud);
		}
		else if (noeud->obtenirType() == ArbreRenduINF2990::NOM_CIBLE)
		{
			((NoeudCible*)noeud)->reinitialiserCible();
		}
	}
	billesEnJeu = 0;
	compteurDeuxiemeBoule = 0;
	points = 0;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::incrementPoints(int points)
///
/// permet dincrementer les points
///
/// @return none
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::incrementPoints(int point)
{
	int p1 = points / arbre_->obtenirPointsBille();
	points += point;
	if (points / arbre_->obtenirPointsBille() == p1 + 1)
	{
		billesRestantes++;
		son_->sonBilleBonus();
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn int FacadeModele::obtenirPoints()
///
/// permet dobtenir les points
///
/// @return nb depoints
///
////////////////////////////////////////////////////////////////////////
int FacadeModele::obtenirPoints()
{
	return points;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn int FacadeModele::obtenirBillesRestantes();
///
/// permet dobtenir les billes restantes
///
/// @return nb de billes
///
////////////////////////////////////////////////////////////////////////
int FacadeModele::obtenirBillesRestantes()const
{
	return billesRestantes;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn int FacadeModele::obtenirBillesRestantes();
///
/// permet dassigner le nombre de billes
///
/// @return nb de billes
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::assignerNbBillesRestante(int billes)
{
	billesRestantes = billes;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::resetPoints()
///
/// permet de reinitialliser les points
///
/// @return void
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::resetPoints()
{
	points = 0;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool FacadeModele::obtenirDifficulteDuXML(std::string nomFichier)
///
/// Cette fonction vas chercher la difficulte dans le xml pour permetre
/// d'ordonner les zones dans une campagne.
///
/// @param[in] string : le nom du fichier pour la lecture de la difficulte
///
/// @return int : difficulte de la zone XML; -1 en cas d'echec de lecture
///
////////////////////////////////////////////////////////////////////////
int FacadeModele::obtenirDifficulteDuXML(char* nomFichier)
{
	/// D?marre le visiteur lire XML
	if (visiteurLireXML == nullptr)
		visiteurLireXML = new VisiteurLireXML();
	/// on ouvre le fichier
	if (visiteurLireXML->ouvrirXML(nomFichier))
	{
		if (visiteurLireXML->verifieXML())
		{
			return visiteurLireXML->obtenirDifficulteXML();
		}
		else
			return -1;
	}
	else
		return -1;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::afficherTexte()
///
/// Cette fonction affiche le texte de la scene
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::afficherTextePoints() const
{
	std::string pointVal = std::to_string(points);
	std::string test = "Points: " + pointVal;
	const char* pointChar = test.c_str();
	myfontPoints->FaceSize(72);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glOrtho(-100.0, 200.0, -200.0, 200.0, -20.0, 20.0);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glScalef(0.1f, 0.1f, 0.1f);
	glTranslatef(-900.0f, 0.0f, 0.0f);
	myfontPoints->Render(pointChar);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::afficherTexte()
///
/// Cette fonction affiche le texte de la scene
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::afficherTexteBille() const
{
	std::string billeVal = std::to_string(billesRestantes);
	std::string test = "Bille restante: " + billeVal;
	const char* pointChar = test.c_str();
	myfontBille->FaceSize(72);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glOrtho(-100.0, 200.0, -200.0, 200.0, -20.0, 20.0);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glScalef(0.1f, 0.1f, 0.1f);
	glTranslatef(-900.0f, 100.0f, 0.0f);
	myfontBille->Render(pointChar);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::inverserAffichageTexte()
///
/// Permet d'inverser la condition d'affichage du texte
///
/// @return void
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::inverserAffichageTexte()
{
	peutAfficher = !peutAfficher;
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
