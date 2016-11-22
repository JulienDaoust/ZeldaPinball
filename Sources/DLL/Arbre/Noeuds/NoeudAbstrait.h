///////////////////////////////////////////////////////////////////////////////
/// @file NoeudAbstrait.h
/// @author DGI-INF2990
/// @date 2007-01-24
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDABSTRAIT_H__
#define __ARBRE_NOEUDS_NOEUDABSTRAIT_H__


#include <windows.h>
#include <GL/gl.h>
#include <string>
#include "../Visiteurs/VisiteurAbstrait.h"
#include "Modele3D.h"
#include "OpenGL_Storage/ModeleStorage_Liste.h"
#include "AideCollision.h"

#include "glm\glm.hpp"

class VisiteurAbstrait;

/// Structure contenant les coins pour un carré englobant
struct BoiteEnglobante{
	glm::dvec3 coinHG;
	glm::dvec3 coinBG;
	glm::dvec3 coinHD;
	glm::dvec3 coinBD;
};

///////////////////////////////////////////////////////////////////////////
/// @class NoeudAbstrait
/// @brief Classe de base du patron composite utilisée pour créer l'arbre
///        de rendu.
///
///        Cette classe abstraite comprend l'interface de base que doivent
///        implanter tous les noeuds pouvant être présent dans l'arbre de
///        rendu.
///
/// @author DGI-2990
/// @date 2007-01-24
///////////////////////////////////////////////////////////////////////////
class NoeudAbstrait
{
public:
	/// Constructeur.
	NoeudAbstrait(
		const std::string& type = std::string{ "" }
	);
	/// Destructeur.
	virtual ~NoeudAbstrait();

	/// Obtient le parent de ce noeud
	inline NoeudAbstrait* obtenirParent();

	/// Obtient le parent de ce noeud (version constante).
	inline const NoeudAbstrait* obtenirParent() const;

	/// Assigne le parent de ce noeud.
	inline void assignerParent(NoeudAbstrait* parent);

	/// Obtient la position relative du noeud.
	inline const glm::dvec3& obtenirPositionRelative() const;

	/// Assigne la position relative du noeud.
	inline void assignerPositionRelative(const glm::dvec3& positionRelative);

	/// Obtient le type du noeud.
	inline const std::string& obtenirType() const;

	/// Obtient la taille relative du noeud
	inline const glm::dvec3& obtenirTailleRelative() const;

	// Assigne la taille relative d'un noeud
	inline void assignerTailleRelative(const glm::dvec3& tailleRelative);
	//permetde scaleup ou scaledown
	inline void scale(const bool scaleUp);

	/// Obtient l'angle de rotation d'un noeud
	inline const double obtenirAngleRotation() const;

	/// Assigne l'angle de rotation d'un noeud
	inline void assignerAngleRotation(const double angleRotation);

	/// Assigne le multiplicateur d'un noeud
	inline void assignerMultiplicateur(const double multi);

	/// Obitent le facteur de multiplication d'un noeud
	inline const double obtenirMultiplicateur() const;

	/// Assigne le nombre de points d'un noeud
	inline void assignerPointCollision(const int point);

	/// Obtient le nombre de point d'un noeud
	inline const int obtenirPointCollision() const;

	/// Écrit l'état de l'affichage du du noeud.
	inline void assignerAffiche(bool affiche);
	/// Vérifie si le noeud se fait afficher.
	inline bool estAffiche() const;
	/// Écrit l'état de la sélection du noeud.
	inline void assignerSelection(bool selectionne);
	/// Vérifie si le noeud est sélectionné.
	inline bool estSelectionne() const;
	/// Écrit si le noeud peut être sélectionné ou non.
	inline void assignerEstSelectionnable(bool selectionnable);
	/// Vérifie si le noeud est sélectionnable.
	inline bool estSelectionnable() const;
	/// Écrit si le noeud peut être enregistré ou non.
	inline void assignerEstEnregistrable(bool enregistrable);
	/// Vérifie si le noeud est enregistrable.
	inline bool estEnregistrable() const;
	/// Vérifie si le noeud est dynamique
	inline bool estDynamique() const;

	/// Verifie si le noeud peut etremis alechelle.
	virtual bool estScaleable() const;
	/// vérifie si el noeud palette
	/// 0 bouge pas
	/// 1 monte
	/// 2 descend
	inline int estAscension() const;
	/// modifie si le noeud palette monte
	inline void assignerEstAscension(int ascension);

	// Interface d'un noeud

	/// Calcule la profondeur de l'arbre sous le noeud courant.
	virtual unsigned int calculerProfondeur() const;

	/// Vide le noeud de ses enfants.
	virtual void vider();
	/// Efface le noeud passé en paramètre.
	virtual void effacer(const NoeudAbstrait* noeud);

	/// Cherche un noeud par le type (sur un noeud constant).
	virtual const NoeudAbstrait* chercher(const std::string& typeNoeud) const;
	/// Cherche un noeud par le type.
	virtual NoeudAbstrait* chercher(const std::string& typeNoeud);
	/// Cherche un noeud enfant selon l'indice (sur un noeud constant).
	virtual const NoeudAbstrait* chercher(unsigned int indice) const;
	/// Cherche un noeud enfant selon l'indice.
	virtual NoeudAbstrait* chercher(unsigned int indice);

	/// Ajoute un noeud enfant.
	virtual bool ajouter(NoeudAbstrait* enfant);
	/// Obtient le nombre d'enfants du noeud.
	virtual unsigned int obtenirNombreEnfants() const;

	/// Changer la sélection du noeud.
	virtual void inverserSelection();
	/// Efface les enfants sélectionnés.
	virtual void effacerSelection();
	/// Sélectionne tous les enfants de même que le noeud.
	virtual void selectionnerTout();
	/// Désélectionne tous les enfants de même que le noeud.
	virtual void deselectionnerTout();
	/// Vérifier si le noeud ou un de ses enfants est sélectionné.
	virtual bool selectionExiste() const;

	/// Change le mode d'affichage des polygones.
	virtual void changerModePolygones(bool estForce);
	/// Assigne le mode d'affichage des polygones.
	virtual void assignerModePolygones(GLenum modePolygones);
	/// Affiche le noeud.
	virtual void afficher() const;
	/// Affiche le noeud de manière concrète.
	virtual void afficherConcret() const;
	/// Anime le noeud.
	virtual void animer(float dt);

	/// desinne la boite englobante autour d'un objet
	virtual void dessinerBoiteEnglobante() const;
	/// retourne la boite englobante
	virtual BoiteEnglobante obtenirBoiteEnglobante();
	/// Accepte le Visiteur
	virtual void accepte(VisiteurAbstrait* Visiteur);

	/// permet d'assigner un valeur a scale_
	virtual void assignerScale(double x, double y, double z);

	/// permet d'effectuer une rotation sur un noeud simple
	virtual void rotation(double angle, glm::dvec3 centre);

	///  retourne le rayon du plus petits cercle contenant l'objet
	virtual double calculerRayon() const;

	/// permet d'identifier les collisions
	virtual aidecollision::DetailsCollision NoeudAbstrait::collision(NoeudAbstrait* noeud);


protected:
	/// Calcule la Boite englobante du noeud
	virtual void calculBoiteEnglobante();

	/// Storage pour le dessin du modèle
	modele::opengl_storage::OpenGL_Liste liste_;
	/// Type du noeud.
	std::string      type_;

	/// Modèle 3D correspondant à ce noeud.
	modele::Modele3D modele_;

	/// Mode d'affichage des polygones.
	GLenum           modePolygones_{ GL_FILL };

	/// Position relative du noeud.
	glm::dvec3         positionRelative_;
	/// Échelle du noeud
	glm::dvec3         scale_{1,1,1};

	/// Axe de rotation
	glm::vec3			myRotationAxis{0,0,1};

	// Angle de rotation du noeud
	double angleRotation = 0;
	
	/// Vrai si on doit afficher le noeud.
	bool             affiche_{ true };

	/// Sélection du noeud.
	bool             selectionne_{ false };

	/// Vrai si le noeud est sélectionnable.
	bool             selectionnable_{ true };

	/// Détermine si l'objet peut être sauvegardé en XML.
	bool             enregistrable_{ true };

	/// Détermine si l'objet est dynamique.
	bool             dynamique_{ false };

	/// détermine si le noeud palette monte
	int			enAscension_{ 0 };
	/// Pointeur vers le parent.
	NoeudAbstrait*   parent_{ nullptr };

	///boite englobante
	BoiteEnglobante boiteEnglobante;

	/// points alloués au joueur lors d'un contact
	int pointCollision = 0;
};




////////////////////////////////////////////////////////////////////////
///
/// @fn inline NoeudAbstrait* NoeudAbstrait::obtenirParent()
///
/// Cette fonction retourne le pointeur vers le parent de ce noeud.
///
/// @return Le pointeur vers le parent.
///
////////////////////////////////////////////////////////////////////////
inline NoeudAbstrait* NoeudAbstrait::obtenirParent()
{
	return parent_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline const NoeudAbstrait* NoeudAbstrait::obtenirParent() const
///
/// Cette fonction retourne le pointeur constant vers le parent de ce noeud.
///
/// @return Le pointeur constant vers le parent.
///
////////////////////////////////////////////////////////////////////////
inline const NoeudAbstrait* NoeudAbstrait::obtenirParent() const
{
	return parent_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerParent( NoeudAbstrait* parent )
///
/// Cette fonction assigne le parent du noeud afin qu'il soit possible
/// de remonter dans l'arbre.
///
/// @param[in] parent : Le parent du noeud.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerParent(
	NoeudAbstrait* parent
	)
{
	parent_ = parent;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline const glm::dvec3& NoeudAbstrait::obtenirPositionRelative() const
///
/// Cette fonction retourne la position relative du noeud par rapport
/// à son parent.
///
/// @return La position relative.
///
////////////////////////////////////////////////////////////////////////
inline const glm::dvec3& NoeudAbstrait::obtenirPositionRelative() const
{
	return positionRelative_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerPositionRelative( const glm::dvec3& positionRelative )
///
/// Cette fonction permet d'assigner la position relative du noeud par
/// rapport à son parent.
///
/// @param positionRelative : La position relative.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerPositionRelative(
	const glm::dvec3& positionRelative
	)
{
	positionRelative_ = positionRelative;
	calculBoiteEnglobante();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline const glm::dvec3& NoeudAbstrait::obtenirTailleRelative() const
///
/// Cette fonction retourne la taille relative du noeud par rapport
/// à son parent.
///
/// @return La taille relative.
///
////////////////////////////////////////////////////////////////////////
inline const glm::dvec3& NoeudAbstrait::obtenirTailleRelative() const
{
	return scale_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerTailleRelative( const glm::dvec3& tailleRelative )
///
/// Cette fonction permet d'assigner la taille relative du noeud par
/// rapport à son parent.
///
/// @param tailleRelative : La taille relative.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerTailleRelative(
	const glm::dvec3& tailleRelative
	)
{
	scale_ = tailleRelative;
	calculBoiteEnglobante();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline const double NoeudAbstrait::obtenirAngleRotation() const
///
/// Cette fonction retourne l'angle de rotation du noeud par rapport
/// à son parent.
///
/// @return L'angle de rotation du noeud.
///
////////////////////////////////////////////////////////////////////////
inline const double NoeudAbstrait::obtenirAngleRotation() const
{
	return angleRotation;
}

/// @fn inline void NoeudAbstrait::assignerAngleRotation( const double angleRotation )
///
/// Cette fonction permet d'assigner l'angle de rotation du noeud par
/// rapport à son parent.
///
/// @param tailleRelative : l'angle de rotation.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerAngleRotation(
	const double angle
	)
{
	angleRotation = angle;
	calculBoiteEnglobante();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn const int NoeudAbstrait::obtenirPointCollision() const
///
/// Cette fonction retourne la valeur associé au point lors d'une
///	collision avec la bille.
///
/// @return Le pointage relié au noeud.
///
////////////////////////////////////////////////////////////////////////
inline const int NoeudAbstrait::obtenirPointCollision() const
{
	return pointCollision;
}

////////////////////////////////////////////////////////////////////////
/// @fn inline void NoeudAbstrait::assignerPointCollision(const int point)
///
/// Cette fonction permet d'assigner la valeur de la collision au noeud
///
/// @param point : la valeur
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerPointCollision(const int point)
{
	pointCollision = point;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline const std::string& NoeudAbstrait::obtenirType() const
///
/// Cette fonction retourne une chaîne représentante le type du noeud.
///
/// @return Le type du noeud.
///
////////////////////////////////////////////////////////////////////////
inline const std::string& NoeudAbstrait::obtenirType() const
{
	return type_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerAffiche( bool affiche )
///
/// Cette fonction permet d'assigner si le noeud se fait afficher ou
/// non lorsque l'arbre de rendu se fait afficher.  Elle permet donc
/// de temporairement suspendre ou activer l'affichage d'un noeud.
///
/// @param affiche : L'état affiché ou non.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerAffiche(bool affiche)
{
	affiche_ = affiche;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudAbstrait::estAffiche() const
///
/// Cette fonction retourne l'état que le noeud se fait afficher ou non.
///
/// @return L'état affiché ou non.
///
////////////////////////////////////////////////////////////////////////
inline bool NoeudAbstrait::estAffiche() const
{
	return affiche_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerSelection( bool selectionne )
///
/// Cette fonction permet d'assigner l'état d'être sélectionné ou non du noeud.
///
/// @param selectionne : L'état sélectionné ou non.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerSelection(bool selectionne)
{
	// Un objet non sélectionnable n'est jamais sélectionné.
	selectionne_ = (selectionne && selectionnable_);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudAbstrait::estSelectionne() const
///
/// Cette fonction retourne l'état d'être sélectionné ou non du noeud.
///
/// @return L'état sélectionné ou non.
///
////////////////////////////////////////////////////////////////////////
inline bool NoeudAbstrait::estSelectionne() const
{
	// Un objet non sélectionnable n'est jamais sélectionné.
	return (selectionne_ && selectionnable_);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerEstSelectionnable( bool selectionnable )
///
/// Cette fonction permet d'assigner l'état d'être sélectionnable ou non du noeud.
///
/// @param selectionnable : L'état sélectionnable ou non.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerEstSelectionnable(bool selectionnable)
{
	selectionnable_ = selectionnable;
	selectionne_ = selectionne_ && selectionnable_;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudAbstrait::estSelectionnable() const
///
/// Cette fonction retourne l'état d'être sélectionnable ou non du noeud.
///
/// @return L'état sélectionnable ou non.
///
////////////////////////////////////////////////////////////////////////
inline bool NoeudAbstrait::estSelectionnable() const
{
	return selectionnable_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerEstEnregistrable( bool enregistrable )
///
/// Cette fonction permet d'assigner l'état d'être entregistrable ou non du noeud.
///
/// @param enregistrable : L'état enregistrable ou non.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerEstEnregistrable(bool enregistrable)
{
	enregistrable_ = enregistrable;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudAbstrait::estEnregistrable() const
///
/// Cette fonction retourne l'état d'être enregistrable en XML ou non du
/// noeud.
///
/// @return L'état enregistrable ou non.
///
////////////////////////////////////////////////////////////////////////
inline bool NoeudAbstrait::estEnregistrable() const
{
	return enregistrable_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerEstAscension( bool valeur )
///
/// Cette fonction permet d'assigner l'état d'être entregistrable ou non du noeud.
///
/// @param enregistrable : L'état enregistrable ou non.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerEstAscension(int valeur)
{
	enAscension_ = valeur;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudAbstrait::estAscension() const
///
/// Cette fonction retourne si le noeud palette monte
///
/// @return L'état enregistrable ou non.
///
////////////////////////////////////////////////////////////////////////
inline int NoeudAbstrait::estAscension() const
{
	return enAscension_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudAbstrait::estDynamique() const
///
/// Cette fonction retourne l'état de dynamique du noeud.
///
/// @return L'état enregistrable ou non.
///
////////////////////////////////////////////////////////////////////////
inline bool NoeudAbstrait::estDynamique() const
{
	return dynamique_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::scale(const bool scaleUp)
///
/// Cette fonction met a lechelleun objet
///
/// @return L'état enregistrable ou non.
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::scale(const bool scaleUp)
{
	if (scaleUp)
	{
		scale_[0] *= 1.02;
		scale_[1] *= 1.02;
		scale_[2] *= 1.02;
	}
	else if (scale_[0] > 0.04 && scale_[1] > 0.04 && scale_[2] > 0.04)
	{
		scale_[0] *= 0.98;
		scale_[1] *= 0.98;
		scale_[2] *= 0.98;
	}
	calculBoiteEnglobante();
}
#endif // __ARBRE_NOEUDS_NOEUDABSTRAIT_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
