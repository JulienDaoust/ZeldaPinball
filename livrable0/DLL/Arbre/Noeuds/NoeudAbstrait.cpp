////////////////////////////////////////////////
/// @file   NoeudAbstrait.cpp
/// @author DGI-2990
/// @date   2007-01-24
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////

#include "NoeudAbstrait.h"
#include "Utilitaire.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait::NoeudAbstrait(const std::string& type)
///
/// Ne fait qu'initialiser les variables membres de la classe.
///
/// @param[in] type               : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait::NoeudAbstrait(
	const std::string& type //= std::string{ "" }
	) :
	type_( type )
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait::~NoeudAbstrait()
///
/// Destructeur vide d�clar� virtuel pour les classes d�riv�es.  La
/// lib�ration des afficheurs n'est pas la responsabilit� de cette
/// classe.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait::~NoeudAbstrait()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn unsigned int NoeudAbstrait::calculerProfondeur() const
///
/// Cette fonction calcule la profondeur de l'arbre incluant le noeud
/// courant ainsi que tous ses enfants.
///
/// Cette fonction retourne toujours 1 pour un noeud sans enfant.
///
/// @return La profondeur de l'arbre sous ce noeud, donc toujours 1.
///
////////////////////////////////////////////////////////////////////////
unsigned int NoeudAbstrait::calculerProfondeur() const
{
	return 1;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::vider()
///
/// Cette fonction vide le noeud de tous ses enfants.
///
/// Cette fonction ne fait rien pour un noeud sans enfant, elle ne fait
/// donc rien dans cette implantation par d�faut de la classe de base.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::vider()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::effacer( const NoeudAbstrait* noeud )
///
/// Cette fonction efface le noeud s'il fait partie des enfants de
/// ce noeud.
///
/// Cette fonction ne fait rien pour un noeud sans enfant, elle ne fait
/// donc rien dans cette implantation par d�faut de la classe de base.
///
/// @param[in] noeud : Le noeud � effacer.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::effacer(const NoeudAbstrait* noeud)
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn const NoeudAbstrait* NoeudAbstrait::chercher( const std::string& typeNoeud ) const
///
/// Cette fonction cherche un noeud d'un type donn� parmi le noeud
/// lui-m�me et ses enfants.
///
/// Elle retourne donc le noeud lui-m�me si son type est celui pass� en
/// param�tre, ou 0 sinon.
///
/// @param[in] typeNoeud : Le type du noeud � trouver.
///
/// @return Le pointeur vers le noeud s'il est trouv�.
///
////////////////////////////////////////////////////////////////////////
const NoeudAbstrait* NoeudAbstrait::chercher(const std::string& typeNoeud) const
{
	if (typeNoeud == type_)
		return this;
	else
		return nullptr;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* NoeudAbstrait::chercher( const std::string& typeNoeud )
///
/// Cette fonction cherche un noeud d'un type donn� parmi le noeud
/// lui-m�me et ses enfants.
///
/// Elle retourne donc le noeud lui-m�me si son type est celui pass� en
/// param�tre, ou 0 sinon.
///
/// @param[in] typeNoeud : Le type du noeud � trouver.
///
/// @return Le pointeur vers le noeud s'il est trouv�.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* NoeudAbstrait::chercher(const std::string& typeNoeud)
{
	if (typeNoeud == type_)
		return this;
	else
		return nullptr;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn const NoeudAbstrait* NoeudAbstrait::chercher( unsigned int indice ) const
///
/// Cette fonction cherche le i-�me enfant d'un noeud.
///
/// Elle retourne toujours 0 pour la classe de base, car cette
/// derni�re ne poss�de pas d'enfant.
///
/// @param[in] indice : L'indice du noeud � trouver.
///
/// @return Le pointeur vers le noeud s'il est trouv�.
///
////////////////////////////////////////////////////////////////////////
const NoeudAbstrait* NoeudAbstrait::chercher(unsigned int indice) const
{
	return nullptr;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* NoeudAbstrait::chercher( unsigned int indice )
///
/// Cette fonction cherche le i-�me enfant d'un noeud.
///
/// Elle retourne toujours 0 pour la classe de base, car cette
/// derni�re ne poss�de pas d'enfant.
///
/// @param[in] indice : L'indice du noeud � trouver.
///
/// @return Le pointeur vers le noeud s'il est trouv�.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* NoeudAbstrait::chercher(unsigned int indice)
{
	return nullptr;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudAbstrait::ajouter(NoeudAbstrait* enfant)
///
/// Cette fonction ajoute un enfant � ce noeud.
///
/// Elle retourne toujours faux et ne fait rien, car ce type de noeud
/// abstrait ne peut pas avoir d'enfant.
///
/// @param[in] enfant: Le noeud � ajouter.
///
/// @return Vrai si l'ajout a bien �t� effectu�, faux autrement.
///
////////////////////////////////////////////////////////////////////////
bool NoeudAbstrait::ajouter(NoeudAbstrait* enfant)
{
	return false;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn unsigned int NoeudAbstrait::obtenirNombreEnfants() const
///
/// Cette fonction retourne le nombre d'enfants de ce noeud.
///
/// Elle retourne toujours 0, car ce type de noeud abstrait ne peut pas
/// avoir d'enfant.
///
/// @return Vrai si l'ajout a bien �t� effectu�, faux autrement.
///
////////////////////////////////////////////////////////////////////////
unsigned int NoeudAbstrait::obtenirNombreEnfants() const
{
	return 0;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::inverserSelection()
///
/// Cette fonction inverse l'�tat de s�lection de ce noeud.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::inverserSelection()
{
	selectionne_ = !selectionne_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::effacerSelection()
///
/// Cette fonction efface les noeuds qui sont s�lectionn�s parmi les
/// enfants de ce noeud.
///
/// Elle ne fait rien, car ce type de noeud abstrait ne peut pas avoir
/// d'enfant.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::effacerSelection()
{
	selectionne_ = false;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::selectionnerTout()
///
/// Cette fonction s�lectionne le noeud et ses enfants.
///
/// Elle ne fait que s�lectionner le noeud pour cette classe, car ce
/// type de noeud abstrait ne peut pas avoir d'enfants.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::selectionnerTout()
{
	assignerSelection(true);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::deselectionnerTout()
///
/// Cette fonction d�s�lectionne le noeud et ses enfants.
///
/// Elle ne fait que d�s�lectionner le noeud pour cette classe, car ce
/// type de noeud abstrait ne peut pas avoir d'enfants.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::deselectionnerTout()
{
	selectionne_ = false;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudAbstrait::selectionExiste() const
///
/// Cette fonction v�rifie si le noeud ou un de ses enfants est
/// s�lectionn�.
///
/// Elle ne fait que regarder si le noeud est s�lectionn�, car ce type
/// de noeud abstrait ne peut pas avoir d'enfants.
///
/// @return Vrai s'il existe un noeud s�lectionn�, faux autrement.
///
////////////////////////////////////////////////////////////////////////
bool NoeudAbstrait::selectionExiste() const
{
	return selectionne_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::changerModePolygones( bool estForce )
///
/// Cette fonction change le mode de rendu des polygones du noeud s'il
/// est s�lectionn� ou si on le force.
///
/// @param[in] estForce: Vrai si on veut changer le mode m�me si le
///                      noeud n'est pas s�lectionn�.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::changerModePolygones(bool estForce)
{
	if ((estForce) || (estSelectionne())) {
		if (modePolygones_ == GL_FILL)
			modePolygones_ = GL_LINE;
		else if (modePolygones_ == GL_LINE)
			modePolygones_ = GL_POINT;
		else
			modePolygones_ = GL_FILL;
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::assignerModePolygones( GLenum modePolygones )
///
/// Cette fonction assigne le mode de rendu des polygones du noeud.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::assignerModePolygones(GLenum modePolygones)
{
	// Le mode par d�faut si on passe une mauvaise valeur est GL_FILL
	if ((modePolygones != GL_FILL) &&
		(modePolygones != GL_LINE) &&
		(modePolygones != GL_POINT)) {
		modePolygones = GL_FILL;
	}

	modePolygones_ = modePolygones;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::afficher() const
///
/// Cette fonction affiche le noeud comme tel.
///
/// Elle consiste en une template method (dans le sens du patron de
/// conception, et non les template C++) qui effectue ce qui est
/// g�n�ralement � faire pour l'affichage, c'est-�-dire:
/// - Mise en pile de la matrice de transformation
/// - Translation du noeud pour qu'il soit � sa position relative
/// - Utilisation du mode d'affichage des polygones
/// - ...
/// - Restauration de l'�tat.
///
/// L'affichage comme tel est confi� � la fonction afficherConcret(),
/// appel�e par la fonction afficher().
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::afficher() const
{
	if (affiche_) {
		glPushMatrix();
		glPushAttrib(GL_CURRENT_BIT | GL_POLYGON_BIT);

		// La translation de la position relative
		glTranslated(
			positionRelative_[0], positionRelative_[1], positionRelative_[2]
			);

		// Assignation du mode d'affichage des polygones
		glPolygonMode(GL_FRONT_AND_BACK, modePolygones_);

		// Affichage concret
		afficherConcret();

		// Restauration
		glPopAttrib();
		glPopMatrix();
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::afficherConcret() const
///
/// Cette fonction effectue le v�ritable rendu de l'objet.  Elle est
/// appel�e par la template method (dans le sens du patron de conception,
/// et non des template C++) afficher() de la classe de base.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::afficherConcret() const
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::animer( float dt )
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps.
///
/// Elle ne fait rien pour cette classe et vise � �tre surcharger par
/// les classes d�riv�es.
///
/// @param[in] dt : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::animer(float dt)
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::calculBoiteEnglobante( glm::dvec3& coinHG, glm::dvec3& coinBG, glm::dvec3& coinHD, glm::dvec3& coinBD )
///
/// Cette fonction calcule la boite englobant un noeud (hitbox)
///
/// @param [in,out] coinHG  : point contenant le coin superieur gauche
/// @param [in,out] coinBG  : point contenant le coin inferieur gauche
/// @param [in,out] coinHD  : point contenant le coin superieur droite
/// @param [in,out] coinBD  : point contenant le coin inferieur droite
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::calculBoiteEnglobante()
{
	if (scale_[0] == 0 && scale_[1] == 0 && scale_[2] == 0)
	{
		scale_[0] = 1;
		scale_[1] = 1;
		scale_[2] = 1;
	}

	utilitaire::BoiteEnglobante boite;
	boite = utilitaire::calculerBoiteEnglobante(modele_);
	double longueur = abs(boite.coinMax[0] - boite.coinMin[0]) * scale_[0];
	double hauteur = abs(boite.coinMax[1] - boite.coinMin[1]) * scale_[1];
	boiteEnglobante.coinHG = { longueur / 2 * -1, hauteur/2, 0 };
	boiteEnglobante.coinBG = { longueur / 2 * -1, hauteur / 2 * -1, 0 };
	boiteEnglobante.coinHD = { longueur / 2, hauteur / 2, 0 };
	boiteEnglobante.coinBD = { longueur / 2 , hauteur / 2 * -1, 0 };
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::assignerScale(double x, double y, double z)
///
/// Cette fonction assigne des valeurs au parametre scale_
///
/// @param [in] x : valeu donner au x de scale
/// @param [in] y : valeu donner au y de scale
/// @param [in] z : valeu donner au z de scale
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::assignerScale(double x, double y, double z)
{
	scale_[0] = x;
	scale_[1] = y;
	scale_[2] = z;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::dessinerBoiteEnglobante()
///
/// Cette fonction effectue le rendu de la boite englobante de l'objet
/// si il est selectionn�
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::dessinerBoiteEnglobante() const
{
	glPushMatrix();
	if (estSelectionne())
	{
		glColor3f(1.0, 0.0, 0.0);
		glLineWidth(3);
		glBegin(GL_LINE_LOOP);

		glVertex3f(boiteEnglobante.coinBD[0], boiteEnglobante.coinBD[1], boiteEnglobante.coinBD[2]);
		glVertex3f(boiteEnglobante.coinHD[0], boiteEnglobante.coinHD[1], boiteEnglobante.coinHD[2]);
		glVertex3f(boiteEnglobante.coinHG[0], boiteEnglobante.coinHG[1], boiteEnglobante.coinHG[2]);
		glVertex3f(boiteEnglobante.coinBG[0], boiteEnglobante.coinBG[1], boiteEnglobante.coinBG[2]);
		glEnd();
		glClearColor(0.0, 0.0, 0.0, 0.0);
	}

	// Restauration de la matrice.
	glPopMatrix();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual  BoiteEnglobante NoeudAbstrait::obtenirBoiteEnglobante( NoeudAbstrait* parent )
///
/// Cette fonction retourne la boite englobante
///
/// @return BoiteEnglobante
///
////////////////////////////////////////////////////////////////////////
BoiteEnglobante NoeudAbstrait::obtenirBoiteEnglobante()
{
	BoiteEnglobante boitePositionnee = boiteEnglobante;
	glm::dvec3 translation = obtenirPositionRelative();

	boitePositionnee.coinHG = { translation[0] + boitePositionnee.coinHG[0], translation[1] + boitePositionnee.coinHG[1], 0 };
	boitePositionnee.coinBG = { translation[0] + boitePositionnee.coinBG[0], translation[1] + boitePositionnee.coinBG[2], 0 };
	boitePositionnee.coinHD = { translation[0] + boitePositionnee.coinHD[0], translation[1] + boitePositionnee.coinHD[2], 0 };
	boitePositionnee.coinBD = { translation[0] + boitePositionnee.coinBD[0], translation[1] + boitePositionnee.coinBD[2], 0 };
	return boitePositionnee;
}


////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////
