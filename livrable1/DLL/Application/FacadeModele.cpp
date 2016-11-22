///////////////////////////////////////////////////////////////////////////////
/// @file FacadeModele.cpp
/// @author Martin Bisson
/// @date 2007-05-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////


// Commentaire Doxygen mis sur la premi�re page de la documentation Doxygen.
/**

@mainpage Projet int�grateur de deuxi�me ann�e -- INF2990

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
// Julien Gascon-Samson, �t� 2011
#include "tinyxml.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

/// Pointeur vers l'instance unique de la classe.
FacadeModele* FacadeModele::instance_{ nullptr };

/// Cha�ne indiquant le nom du fichier de configuration du projet.
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
/// classe.  Si cette instance n'a pas �t� cr��e, elle la cr�e.  Cette
/// cr�ation n'est toutefois pas n�cessairement "thread-safe", car
/// aucun verrou n'est pris entre le test pour savoir si l'instance
/// existe et le moment de sa cr�ation.
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
/// Cette fonction lib�re l'instance unique de cette classe.
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
/// Ce destructeur lib�re les objets du mod�le.
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
/// Cette fonction permet d'initialiser le contexte OpenGL.  Elle cr�e
/// un contexte OpenGL sur la fen�tre pass�e en param�tre, initialise
/// FreeImage (utilis�e par le chargeur de mod�les) et assigne des 
/// param�tres du contexte OpenGL.
///
/// @param[in] hWnd : La poign�e ("handle") vers la fen�tre � utiliser.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::initialiserOpenGL(HWND hWnd)
{
	hWnd_ = hWnd;
	bool succes{ aidegl::creerContexteGL(hWnd_, hDC_, hGLRC_) };
	assert(succes && "Le contexte OpenGL n'a pu �tre cr��.");

	// Initialisation des extensions de OpenGL
	glewInit();

	// Initialisation de la configuration
	chargerConfiguration();

	// FreeImage, utilis�e par le chargeur, doit �tre initialis�e
	FreeImage_Initialise();

	// La couleur de fond
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Les lumi�res
	glEnable(GL_LIGHTING);
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glEnable(GL_COLOR_MATERIAL);
	/// Pour normaliser les normales dans le cas d'utilisation de glScale[fd]
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHT0);

	// Qualit�
	glShadeModel(GL_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	// Profondeur
	glEnable(GL_DEPTH_TEST);

	// Le cull face
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);


	// Cr�ation de l'arbre de rendu.  � moins d'�tre compl�tement certain
	// d'avoir une bonne raison de faire autrement, il est plus sage de cr�er
	// l'arbre apr�s avoir cr�� le contexte OpenGL.
	arbre_ = new ArbreRenduINF2990;
	arbre_->initialiser();

	// On cr�e une vue par d�faut.
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
/// Cette fonction charge la configuration � partir d'un fichier XML si
/// ce dernier existe.  Sinon, le fichier de configuration est g�n�r� �
/// partir de valeurs par d�faut directement dans le code.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::chargerConfiguration() const
{
	// V�rification de l'existance du ficher

	// Si le fichier n'existe pas, on le cr�e.
	if (!utilitaire::fichierExiste(FICHIER_CONFIGURATION)) {
		enregistrerConfiguration();
	}
	// si le fichier existe on le lit
	else {
		TiXmlDocument document;

		// Lire � partir du fichier de configuration
		document.LoadFile(FacadeModele::FICHIER_CONFIGURATION.c_str());

		// On lit les diff�rentes configurations.
		ConfigScene::obtenirInstance()->lireDOM(document);
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::enregistrerConfiguration() const
///
/// Cette fonction g�n�re un fichier XML de configuration � partir de
/// valeurs par d�faut directement dans le code.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::enregistrerConfiguration() const
{
	TiXmlDocument document;

	// �crire la d�claration XML standard...
	TiXmlDeclaration* declaration{ new TiXmlDeclaration{ "1.0", "", "" } };
	document.LinkEndChild(declaration);

	// On enregistre les diff�rentes configurations.
	ConfigScene::obtenirInstance()->creerDOM(document);

	// �crire dans le fichier
	document.SaveFile(FacadeModele::FICHIER_CONFIGURATION.c_str());
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::libererOpenGL()
///
/// Cette fonction lib�re le contexte OpenGL et d�sinitialise FreeImage.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::libererOpenGL()
{
	utilitaire::CompteurAffichage::libererInstance();

	// On lib�re les instances des diff�rentes configurations.
	ConfigScene::libererInstance();


	bool succes{ aidegl::detruireContexteGL(hWnd_, hDC_, hGLRC_) };
	assert(succes && "Le contexte OpenGL n'a pu �tre d�truit.");

	FreeImage_DeInitialise();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::afficher() const
///
/// Cette fonction affiche le contenu de la sc�ne.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::afficher() const
{
	// Efface l'ancien rendu
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Ne devrait pas �tre n�cessaire
	vue_->appliquerProjection();

	// Positionne la cam�ra
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	vue_->appliquerCamera();

	// Afficher la sc�ne
	afficherBase();

	// Compte de l'affichage
	utilitaire::CompteurAffichage::obtenirInstance()->signalerAffichage();

	// �change les tampons pour que le r�sultat du rendu soit visible.
	::SwapBuffers(hDC_);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::afficherBase() const
///
/// Cette fonction affiche la base du contenu de la sc�ne, c'est-�-dire
/// qu'elle met en place l'�clairage et affiche les objets.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::afficherBase() const
{
	// Positionner la lumi�re.
	glm::vec4 position{ 0, 0, 1, 0 };
	glLightfv(GL_LIGHT0, GL_POSITION, glm::value_ptr(position));

	// Afficher la sc�ne.
	arbre_->afficher();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::reinitialiser()
///
/// Cette fonction r�initialise la sc�ne � un �tat "vide".
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::reinitialiser()
{
	// R�initialisation de la sc�ne.
	arbre_->initialiser();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::animer(float temps)
///
/// Cette fonction effectue les diff�rents calculs d'animations
/// n�cessaires pour le mode jeu, tel que les diff�rents calculs de
/// physique du jeu.
///
/// @param[in] temps : Intervalle de temps sur lequel effectuer le calcul.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::animer(float temps)
{
	// Mise � jour des objets.
	arbre_->animer(temps);

	// Mise � jour de la vue.
	vue_->animer(temps);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::ajouterNoeud(std::string nom, glm::dvec3& point)
///
/// Cette fonction ajoute un noeud a l'arbre de rendu et modifie sa position relative selon l'endroi 
///
/// @param[in] nom : nom du type d'objet a cr��
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
/// @param[in] x : position en x de l'objet recherch�
///
/// @param[in] y : position en y del'objet recherch�
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
/// @param[in] min,max : sommet dela boite dans laquelle on s�lectionne les objets
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
/// Cette fonction effectue une mise � l'�chelle sur les objets de la scene
///
/// @param[in] point : point qui repr�sente la position de la souris
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
/// Cette fonction effectue une duplication des objets selectionn�s
///
/// @param[in] point : point qui repr�sente la position de la souris
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
/// @return bool : facteur de s�curit� (� venir)
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
/// Cette fonction supprime les objets s�lectionn�es de la scene
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
/// @return bool : facteur de s�curit�
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
/// @return bool : facteur de s�curit� (� venir)
///
////////////////////////////////////////////////////////////////////////
bool FacadeModele::lectureXML(char* nomFichier)
{
	/// D�marre le visiteur lire XML
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
