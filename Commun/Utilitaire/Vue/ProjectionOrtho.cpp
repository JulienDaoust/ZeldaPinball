////////////////////////////////////////////////////////////////////////////////////
/// @file ProjectionOrtho.cpp
/// @author DGI
/// @date 2006-12-15
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <GL/gl.h>
#include "ProjectionOrtho.h"
#include "Vue.h"
#include "iostream"


namespace vue {


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn ProjectionOrtho::ProjectionOrtho(int xMinCloture, int xMaxCloture, int yMinCloture, int yMaxCloture, double zAvant,  double zArriere, double zoomInMax, double zoomOutMax, double incrementZoom, double xMinFenetre, double xMaxFenetre, double yMinFenetre, double yMaxFenetre)
	///
	/// Constructeur d'une projection orthogonale.  Ne fait qu'assigner les
	/// variables membres et ajuste ensuite le rapport d'aspect.
	///
	/// @param[in] xMinCloture   : coordonnée minimale en @a x de la clôture.
	/// @param[in] xMaxCloture   : coordonnée maximale en @a x de la clôture.
	/// @param[in] yMinCloture   : coordonnée minimale en @a y de la clôture.
	/// @param[in] yMaxCloture   : coordonnée maximale en @a y de la clôture.
	/// @param[in] zAvant        : distance du plan avant (en @a z).
	/// @param[in] zArriere      : distance du plan arrière (en @a z).
	/// @param[in] zoomInMax     : facteur de zoom in maximal.
	/// @param[in] zoomOutMax    : facteur de zoom out maximal.
	/// @param[in] incrementZoom : distance du plan arrière (en @a z).
	/// @param[in] xMinFenetre   : coordonnée minimale en @a x de la fenêtre
	///                            virtuelle.
	/// @param[in] xMaxFenetre   : coordonnée maximale en @a x de la fenêtre
	///                            virtuelle.
	/// @param[in] yMinFenetre   : coordonnée minimale en @a y de la fenêtre
	///                            virtuelle.
	/// @param[in] yMaxFenetre   : coordonnée maximale en @a y de la fenêtre
	///                            virtuelle.
	/// 
	/// @return Aucune (constructeur).
	///
	////////////////////////////////////////////////////////////////////////
	ProjectionOrtho::ProjectionOrtho(int xMinCloture, int xMaxCloture,
		int yMinCloture, int yMaxCloture,
		double zAvant, double zArriere,
		double zoomInMax, double zoomOutMax,
		double incrementZoom,
		double xMinFenetre, double xMaxFenetre,
		double yMinFenetre, double yMaxFenetre) :
		Projection{ xMinCloture, xMaxCloture, yMinCloture, yMaxCloture,
		zAvant, zArriere,
		zoomInMax, zoomOutMax, incrementZoom, false },
		xMinFenetre_{ xMinFenetre },
		xMaxFenetre_{ xMaxFenetre },
		yMinFenetre_{ yMinFenetre },
		yMaxFenetre_{ yMaxFenetre }
	{
		ajusterRapportAspect();
		mettreAJourCloture();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::zoomerIn()
	///
	/// Permet de faire un zoom in selon l'incrément de zoom.
	/// 
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::zoomerIn()
	{
		if (nbZoom > -8)
		{
			xMaxFenetre_ = xMaxFenetre_ / (incrementZoom_);
			yMaxFenetre_ = yMaxFenetre_ / (incrementZoom_);
			xMinFenetre_ = xMinFenetre_ / (incrementZoom_);
			yMinFenetre_ = yMinFenetre_ / (incrementZoom_);
			nbZoom--;
			ajusterRapportAspect();
		}
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::zoomerOut()
	///
	/// Permet de faire un zoom out selon l'incrément de zoom.
	///
	/// @return Aucune.
	///
	//////////////////////////////////////////////////////////////////////// 
	void ProjectionOrtho::zoomerOut()
	{
		if (nbZoom < 5)
		{
			xMaxFenetre_ = (incrementZoom_)*xMaxFenetre_;
			yMaxFenetre_ = (incrementZoom_)*yMaxFenetre_;
			xMinFenetre_ = (incrementZoom_)*xMinFenetre_;
			yMinFenetre_ = (incrementZoom_)*yMinFenetre_;
			nbZoom++;
			ajusterRapportAspect();
		}
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::redimensionnerFenetre( const glm::ivec2& coinMin, const glm::ivec2& coinMax )
	///
	/// Permet d'ajuster les coordonnées de la fenêtre virtuelle en fonction
	/// d'un redimensionnement de la fenêtre.
	///
	/// L'agrandissement de la fenêtre virtuelle est proportionnel à
	/// l'agrandissement de la clotûre afin que les objets gardent la même
	/// grandeur apparente lorsque la fenêtre est redimensionnée.
	///
	/// @param[in]  coinMin : Coin contenant les coordonnées minimales de la
	///                       nouvelle clôture
	/// @param[in]  coinMax : Coin contenant les coordonnées maximales de la
	///                       nouvelle clôture
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::redimensionnerFenetre(const glm::ivec2& coinMin,
		const glm::ivec2& coinMax)
	{
		double ratiox = coinMax.x - xMaxCloture_;
		double ratioy = coinMax.y - yMaxCloture_;

		ratiox = ratiox*((xMaxFenetre_ - xMinFenetre_) / xMaxCloture_);
		ratioy = ratioy*((yMaxFenetre_ - yMinFenetre_) / yMaxCloture_);

		xMinFenetre_ = xMinFenetre_ - ratiox / 2;
		yMinFenetre_ = yMinFenetre_ - ratioy / 2;

		xMaxFenetre_ = xMaxFenetre_ - ratiox / 2;
		yMaxFenetre_ = yMaxFenetre_ - ratioy / 2;

		xMinCloture_ = coinMin.x;
		yMaxCloture_ = coinMin.y;
		xMaxCloture_ = coinMax.x;
		yMaxCloture_ = coinMax.y;

		ajusterRapportAspect();
		mettreAJourCloture();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::appliquer() const
	///
	/// Cette fonction permet d'appliquer la fenêtre virtuelle en appelant les
	/// fonctions d'OpenGL selon le type de projection et les propriétés de la
	/// fenêtre.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::appliquer() const
	{
		glOrtho(xMinFenetre_, xMaxFenetre_,
			yMinFenetre_, yMaxFenetre_,
			zAvant_, zArriere_);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::zoomerIn( const glm::ivec2& coin1, const glm::ivec2& coin2)
	///
	/// Permet de faire un zoom in sur un rectangle déterminé par deux coins.
	/// Ainsi la région délimitée par le rectangle deviendra la fenêtre
	/// virtuelle.  La fenêtre résultante est ajustée pour respecter le rapport
	/// d'aspect.
	///
	/// @param[in]  coin1 : Le premier coin du rectangle.
	/// @param[in]  coin2 : Le deuxième coin du rectangle.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::zoomerIn(const glm::dvec3& coin1, const glm::dvec3& coin2)
	{
		double longueurXElast = abs(coin1.x - coin2.x);
		double longueurYElast = abs(coin1.y - coin2.y);
		double diagonaleElast = sqrt((longueurXElast*longueurXElast) + (longueurYElast*longueurYElast));		 
		
		double diffX = xMaxCloture_ - xMinCloture_;
		double diffy = yMaxCloture_ - yMinCloture_;
		double diagonaleCloture = sqrt((diffX*diffX) + (diffy*diffy));

		double rapportDiago = diagonaleCloture / diagonaleElast;

		xMaxFenetre_ = xMaxFenetre_*rapportDiago;
		yMaxFenetre_ = yMaxFenetre_*rapportDiago;

		xMinFenetre_ = xMinFenetre_ * rapportDiago;
		yMinFenetre_ = yMinFenetre_ * rapportDiago;

		centrerSurPoint(centre_);
		ajusterRapportAspect();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::zoomerOut( const glm::ivec2& coin1, const glm::ivec2& coin2)
	///
	/// Permet de faire un zoom out sur un rectangle délimité par deux coins.
	/// Ainsi la fenêtre virtuelle avant le zoom sera placée à l'interieur de
	/// la région délimité par le rectangle.  La fenêtre résultante est ajustée
	/// pour respecter le rapport d'aspect.
	///
	/// @param[in]  coin1 : Le premier coin du rectangle.
	/// @param[in]  coin2 : Le deuxième coin du rectangle.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::zoomerOut(const glm::dvec3& coin1, const glm::dvec3& coin2)
	{
		double longueurXElast = abs(coin1.x - coin2.x);
		double longueurYElast = abs(coin1.y - coin2.y);
		double diagonaleElast = sqrt((longueurXElast*longueurXElast) + (longueurYElast*longueurYElast));

		double diffX = xMaxCloture_ - xMinCloture_;
		double diffy = yMaxCloture_ - yMinCloture_;
		double diagonaleCloture = sqrt((diffX*diffX) + (diffy*diffy));

		double rapportDiago = diagonaleCloture / diagonaleElast;

		xMaxFenetre_ = xMaxFenetre_*rapportDiago;
		yMaxFenetre_ = yMaxFenetre_*rapportDiago;

		xMinFenetre_ = xMinFenetre_ * rapportDiago;
		yMinFenetre_ = yMinFenetre_ * rapportDiago;

		centrerSurPoint(centre_);
		ajusterRapportAspect();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::translater( double deplacementX, double deplacementY )
	///
	/// Permet de déplacer la fenêtre virtuelle en @a x et en @a y.  Les
	/// déplacement doivent être exprimés en proportion de la fenêtre virtuelle.
	///
	/// @param[in]  deplacementX : le déplacement en @a x.
	/// @param[in]  deplacementY : le déplacement en @a y.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::translater(double deplacementX, double deplacementY)
	{
		double diffx = xMaxFenetre_ - xMinFenetre_;
		double diffy = yMaxFenetre_ - yMinFenetre_;

		double deplX = diffx * 0.1;
		double deplY = diffy * 0.1;

		//deplacement à droite
		if (deplacementX == 1 && deplacementY == 0)
		{
			xMaxFenetre_ = xMaxFenetre_ - deplX;
			xMinFenetre_ = xMinFenetre_ - deplX;
		}  

		//deplacement à gauche
		else if (deplacementX == -1 && deplacementY == 0)
		{
			xMaxFenetre_ = xMaxFenetre_ + deplX;
			xMinFenetre_ = xMinFenetre_ + deplX;
		}

		//deplacement en haut
		else if (deplacementX == 0 && deplacementY == 1)
		{
			yMaxFenetre_ = yMaxFenetre_ - deplY;
			yMinFenetre_ = yMinFenetre_ - deplY;
		}

		//deplacement en bas
		else if (deplacementX == 0 && deplacementY == -1)
		{
			yMaxFenetre_ = yMaxFenetre_ + deplY;
			yMinFenetre_ = yMinFenetre_ + deplY;
		}

		else
		{
			xMaxFenetre_ = xMaxFenetre_ + deplacementX;
			xMinFenetre_ = xMinFenetre_ + deplacementX;
			yMaxFenetre_ = yMaxFenetre_ + deplacementY;
			yMinFenetre_ = yMinFenetre_ + deplacementY;
		}

		centre_ = glm::ivec2((xMaxFenetre_ + xMinFenetre_) / 2, (yMaxFenetre_ + yMinFenetre_) / 2);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::translater(const glm::ivec2& deplacement)
	///
	/// Permet de translater la fenêtre virtuelle en fonction d'un déplacement
	/// en coordonnées de clôture.
	///
	/// @param[in]  deplacement : Le déplacement en coordonnées de clôture.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::translater(const glm::dvec2& deplacement)
	{
		xMaxFenetre_ = xMaxFenetre_ + deplacement.x;
		xMinFenetre_ = xMinFenetre_ + deplacement.x;
		yMaxFenetre_ = yMaxFenetre_ + deplacement.y;
		yMinFenetre_ = yMinFenetre_ + deplacement.y;

		centre_ = glm::dvec2((xMaxFenetre_ + xMinFenetre_) / 2, (yMaxFenetre_ + yMinFenetre_) / 2);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::centrerSurPoint( const glm::ivec2& pointCentre )
	///
	/// Permet de centrer la fenêtre virtuelle sur un point de l'écran. Le
	/// point de l'écran est convertit en coordonnées virtuelles et il devient
	/// le centre de la fenêtre virtuelle.
	///
	/// @param[in]  pointCentre : Le point sur lequel on doit centrer.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::centrerSurPoint(const glm::dvec2& pointCentre)
	{
		double xTranslate = pointCentre.x - (xMaxFenetre_ + xMinFenetre_) / 2;
		double yTranslate = pointCentre.y - (yMaxFenetre_ + yMinFenetre_) / 2;

		centre_ = glm::dvec2(xTranslate, yTranslate);

		translater(centre_);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::ajusterRapportAspect()
	///
	/// Permet d'ajuster les coordonnées de la fenêtre virtuelle en fonction
	/// de la clôture de façon à ce que le rapport d'aspect soit respecté.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::ajusterRapportAspect()
	{
		if ((xMaxFenetre_ - xMinFenetre_)*(double)yMaxCloture_ / (double)xMaxCloture_ >= (yMaxFenetre_ - yMinFenetre_)*(double)xMaxCloture_ / (double)yMaxCloture_)
		{
			yMinFenetre_ = (xMinFenetre_)*(double)yMaxCloture_ / (double)(xMaxCloture_);
			yMaxFenetre_ = (xMaxFenetre_)*(double)yMaxCloture_ / (double)(xMaxCloture_);
		}
		else
		{
			xMinFenetre_ = yMinFenetre_*(double)xMaxCloture_ / (double)(yMaxCloture_);
			xMaxFenetre_ = yMaxFenetre_*(double)xMaxCloture_ / (double)(yMaxCloture_);
		}
		centrerSurPoint(centre_);
	}

}; // Fin du namespace vue.


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
