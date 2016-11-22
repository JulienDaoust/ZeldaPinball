using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using InterfaceGraphique.patron_state;
using System.IO;

namespace InterfaceGraphique
{
    /// <summary>
    /// Fenetre qui servira au mode editeur et au mode test
    /// </summary>
    public partial class ModeEditeur : Form
    {

        /// <summary>
        /// Constantes des noms des objets
        /// </summary>
        public const String NOM_PALETTE_JOUEUR1_GAUCHE = "paletteJoueur1Gauche\0";
        public const String NOM_PALETTE_JOUEUR1_DROITE = "paletteJoueur1Droite\0";
        public const String NOM_PALETTE_JOUEUR2_GAUCHE = "paletteJoueur2Gauche\0";
        public const String NOM_PALETTE_JOUEUR2_DROITE = "paletteJoueur2Droite\0";
        public const String NOM_BUTOIR_TRIANGULAIRE_GAUCHE = "butoirTriangulaireGauche\0";
        public const String NOM_BUTOIR_TRIANGULAIRE_DROIT = "butoirTriangulaireDroit\0";
        public const String NOM_BUTOIR_CIRCULAIRE = "butoirCirculaire\0";
        public const String NOM_CIBLE = "cible\0";
        public const String NOM_RESSORT = "ressort\0";
        public const String NOM_GENERATEUR_BILLE = "generateurBille\0";
        public const String NOM_TROU = "trou\0";
        public const String NOM_PORTAIL = "portail\0";
        public const String NOM_MUR = "mur\0";
        public const String NOM_BILLE = "bille\0";


        /// <summary>
        /// Fenetre des propriete
        /// </summary>
        Propriete prop;
        /// <summary>
        /// Fenetre du menu principal
        /// </summary>
        MenuPrincipal menu;
        /// <summary>
        /// et atribut représente l'objet a etre créé au prochain click
        /// </summary>
        string creationObjetClick = null;
        /// <summary>
        /// Cet attribut determine si on dessine la boite elastique
        /// </summary>
        Boolean rectangleElastiqueActif = false;
        /// <summary>
        /// Cet atribut garde la position de la souris au moment de l'évènement panel1_MouseDown() 
        /// </summary>
        Point positionRectangleElastiqueInitial;
        /// <summary>
        /// Cet atribut garde la position de la souris au moment de l'évènement panel1_MouseDown() 
        /// </summary>
        Point positionRectangleElastiqueFinal = new Point(-1, -1);
        /// <summary>
        /// le rectangle elastique
        /// </summary>
        Rectangle rectangleElastique;
        /// <summary>
        /// la variable d'état
        /// </summary>
        AbstractState state;
        /// <summary>
        /// la variable d'état de la vue
        /// </summary>
        AbstractState viewState = new ViewPerspectiveState();
        /// <summary>
        /// la variable nous indiquant si la fenetre est active
        /// </summary>
        Boolean isActive = true;
        /// <summary>
        // /x au mousedown
        /// </summary>
        int mdX;
        /// <summary>
        /// y au mousedown
        /// </summary>
        int mdY;
        /// <summary>
        /// s au mouseup
        /// </summary>
        int muX;
        /// <summary>
        /// y au mouseup
        /// </summary>
        int muY;
        //En pause
        bool pause = false;
        //boolean qui vérifie si la touche de la palette gauche du joueur 1 est gardé enfoncé
        bool PGJ1isPressed = false;
        //boolean qui vérifie si la touche de la palette droite du joueur 1 est gardé enfoncé
        bool PDJ1isPressed = false;
        //boolean qui vérifie si la touche de la gauche droite du joueur 2 est gardé enfoncé
        bool PGJ2isPressed = false;
        //boolean qui vérifie si la touche de la palette droite du joueur 2 est gardé enfoncé
        bool PDJ2isPressed = false;
        //boolean qui vérifie si la touche du ressort est gardé enfoncé
        bool ressortPressed = false;
        ///Tableau des touches pour jouer dans la configuration
        Keys[] touches = new Keys[5];
        ///Tableau des touches pour jouer dans la configuration
        bool[] debug = new bool[5];
        //Lumiere ambiante
        bool lumAmbiante = false;
        //Lumiere directionnelle
        bool lumDirect = false;
        //Spotlights
        bool spotlights = false;

        /// <summary>
        /// Constructeur avec le menu principal en parametre
        /// </summary>
        /// <param name="menu1">menu principal</param>
        public ModeEditeur(MenuPrincipal menu1)
        {
            FonctionsNatives.reinitialiser();
            this.KeyPreview = true;
            this.KeyUp += new KeyEventHandler(ToucheEnfonce);
            this.KeyDown += new KeyEventHandler(ToucheDown);
            this.MouseWheel += new MouseEventHandler(panel1_MouseWheel);

            Application.AddMessageFilter(new MouseMessageFilter());
            InitializeComponent();
            InitialiserAnimation();
            menu = menu1;
            menuStrip2.Hide();
            recupererTouches();
            recupererDebug();
            ribbonButtonSelection.Checked = false;
            panel1.Size = new System.Drawing.Size(1214, 753);
        }
        /// <summary>
        /// Fonction qui est appelle a chaque trame d'affichage
        /// </summary>
        /// <param name="tempsInterAffichage">temps entre chaque trame</param>
        public void MettreAJour(double tempsInterAffichage)
        {
            if (isActive)
            {
                if (!(state is TestState))
                    FonctionsNatives.redimensionnerFenetre(panel1.Width, panel1.Height - menuStrip1.Height - ribbon1.Height);
                else if (menuStrip2.Visible)
                    FonctionsNatives.redimensionnerFenetre(panel1.Width, panel1.Height - menuStrip2.Height);
                else
                    FonctionsNatives.redimensionnerFenetre(panel1.Width, panel1.Height);
            } if (state is TestState && !pause)
            {
                try
                {
                    this.Invoke((MethodInvoker)delegate
                    {
                        FonctionsNatives.animer(tempsInterAffichage);

                    });
                }
                catch (Exception)
                {
                }
            }
            FonctionsNatives.dessinerOpenGL();
        }

        /// <summary>
        /// Classe fournie par le cadriciel
        /// </summary>
        class MouseMessageFilter : IMessageFilter
        {
            public static event MouseEventHandler MouseMove = delegate { };
            const int WM_MOUSEMOVE = 0x0200;

            public bool PreFilterMessage(ref Message m)
            {

                if (m.Msg == WM_MOUSEMOVE)
                {

                    Point mousePosition = Control.MousePosition;

                    MouseMove(null, new MouseEventArgs(
                        MouseButtons.None, 0, mousePosition.X, mousePosition.Y, 0));
                }
                return false;
            }
        }

        /// <summary>
        /// On initialise la scene
        /// </summary>
        public void InitialiserAnimation()
        {
            this.DoubleBuffered = true;
            FonctionsNatives.initialiserOpenGL(panel1.Handle);
            FonctionsNatives.dessinerOpenGL();
        }

        /// <summary>
        /// Fonction qui recupere les touches du fichier de config
        /// </summary>
        private void recupererTouches()
        {
            string pathConfig = Application.StartupPath + "/données/Config.txt";
            string[] touche = System.IO.File.ReadAllLines(pathConfig);
            touches[0] = (Keys)Enum.Parse(typeof(Keys), touche[0]);
            touches[1] = (Keys)Enum.Parse(typeof(Keys), touche[1]);
            touches[2] = (Keys)Enum.Parse(typeof(Keys), touche[2]);
            touches[3] = (Keys)Enum.Parse(typeof(Keys), touche[3]);
            touches[4] = (Keys)Enum.Parse(typeof(Keys), touche[4]);
        }

        /// <summary>
        /// Fonction qui recupere les configs de debug du fichier de config
        /// </summary>
        private void recupererDebug()
        {
            string pathConfig = Application.StartupPath + "/données/Config.txt";
            string[] valeursDebug = new string[5];
            string[] touche = System.IO.File.ReadAllLines(pathConfig);
            valeursDebug[0] = touche[7];
            valeursDebug[1] = touche[8];
            valeursDebug[2] = touche[9];
            valeursDebug[3] = touche[10];
            valeursDebug[4] = touche[11];
            if (valeursDebug[0] == "Desactiver")
            {
                for (int i = 0; i < 5; i++)
                {
                    debug[i] = false;
                }
            }
            else if (valeursDebug[0] == "Activer")
            {
                debug[0] = true;
                for (int i = 1; i < 5; i++)
                {
                    if (valeursDebug[i] == "Oui")
                        debug[i] = true;
                    else if (valeursDebug[i] == "Non")
                        debug[i] = false;
                }
            }
            FonctionsNatives.assignerDebug(debug);
        }

        /// <summary>
        /// Fonction appellee quand une touche est relachee
        /// </summary>
        /// <param name="o"></param>
        /// <param name="e"></param>
        private void ToucheEnfonce(Object o, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.D2)
            {
                viewState = new ViewPerspectiveState();
                FonctionsNatives.changeToPerspective();
            }

            if (e.KeyCode == Keys.D1)
            {
                viewState = new ViewOrthoState();
                FonctionsNatives.changeToOrtho();
            }

            if (e.KeyValue == (char)Keys.Subtract || (e.KeyValue == (char)Keys.OemMinus))
            {
                FonctionsNatives.zoomOut();
            }

            if (e.KeyValue == (char)Keys.Add || (e.KeyValue == (char)Keys.Oemplus && e.Modifiers == Keys.Shift))
            {
                FonctionsNatives.zoomIn();
            }
            if (viewState is ViewOrthoState)
            {
                if (e.KeyValue == (char)Keys.Up)
                {
                    FonctionsNatives.translater(0, 1);
                }

                if (e.KeyValue == (char)Keys.Left)
                {
                    FonctionsNatives.translater(-1, 0);
                }

                if (e.KeyValue == (char)Keys.Down)
                {
                    FonctionsNatives.translater(0, -1);
                }

                if (e.KeyValue == (char)Keys.Right)
                {
                    FonctionsNatives.translater(1, 0);
                }
            }
            if (viewState is ViewPerspectiveState)
            {
                if (e.KeyValue == (char)Keys.Up)
                {
                    FonctionsNatives.rotaterXY(0, 0.05);
                }

                if (e.KeyValue == (char)Keys.Left)
                {
                    FonctionsNatives.rotaterXY(0.05, 0);
                }

                if (e.KeyValue == (char)Keys.Down)
                {
                    FonctionsNatives.rotaterXY(0, -0.05);
                }

                if (e.KeyValue == (char)Keys.Right)
                {
                    FonctionsNatives.rotaterXY(-0.05, 0);
                }
            }

            if (!(state is TestState))
            {
                if (e.KeyValue == (char)Keys.Escape)
                {
                    FonctionsNatives.validateMouvement();
                    FonctionsNatives.releaseVisiteurs();
                    creationObjetClick = null;
                    state = null;
                    resetToolInterface();
                    ribbonButtonSelection.Checked = false;
                }

                if (e.KeyCode == Keys.Q && ModifierKeys == Keys.Control)
                {
                    menu.Show();
                    isActive = false;
                    this.Close();
                }

                if (e.KeyCode == Keys.T)
                {
                    state = new TestState();
                    menuStrip1.Hide();
                    ribbon1.Hide();
                    //panelRotation.Hide();

                }
            }
            else
            {
                if (e.KeyCode == Keys.T)
                {
                    FonctionsNatives.reinitialiserPartie();
                    state = null;
                    pause = false;
                    menuStrip1.Show();
                    menuStrip2.Hide();
                    ribbon1.Show();
                    //panelRotation.Show();

                }

                if (e.KeyValue == (char)Keys.Escape && pause == false)
                {
                    pause = true;
                    menuStrip2.Show();
                    e.Handled = true;
                }
                if (e.KeyValue == (char)Keys.Escape && pause == true && e.Handled == false)
                {
                    pause = false;
                    menuStrip2.Hide();
                    e.Handled = true;
                }

                if (e.KeyCode == touches[0] && PGJ1isPressed)
                {
                    FonctionsNatives.animerPaletteGJ1(false);
                    PGJ1isPressed = false;
                }
                if (e.KeyCode == touches[1] && PDJ1isPressed)
                {
                    FonctionsNatives.animerPaletteDJ1(false);
                    PDJ1isPressed = false;
                }
                if (e.KeyCode == touches[4] && ressortPressed)
                {
                    FonctionsNatives.animerRessort(false);
                    ressortPressed = false;
                }
                if (e.KeyValue == (char)Keys.Back)
                {
                    FonctionsNatives.reinitialiserPartie();
                }

                if (e.KeyCode == Keys.J)
                {
                    lumAmbiante = !lumAmbiante;
                    FonctionsNatives.changeLumAmbiant();
                    DateTime temps = DateTime.Now;
                    if (lumAmbiante && debug[3])
                        Console.WriteLine("{0:hh:mm:ss.fff} - Lumiere AMBIANTE OUVERTE", temps);
                    else if (debug[3])
                        Console.WriteLine("{0:hh:mm:ss.fff} - Lumiere AMBIANTE FERMEE", temps);
                }
                if (e.KeyCode == Keys.K)
                {
                    lumDirect = !lumDirect;
                    FonctionsNatives.changeLumDirect();
                    DateTime temps = DateTime.Now;
                    if (lumDirect && debug[3])
                        Console.WriteLine("{0:hh:mm:ss.fff} - Lumiere DIRECTIONELLE OUVERTE", temps);
                    else if (debug[3])
                        Console.WriteLine("{0:hh:mm:ss.fff} - Lumiere DIRECTIONELLE FERMEE", temps);
                }
                if (e.KeyCode == Keys.L)
                {
                    spotlights = !spotlights;
                    FonctionsNatives.changeLumSpot();
                    DateTime temps = DateTime.Now;
                    if (spotlights && debug[3])
                        Console.WriteLine("{0:hh:mm:ss.fff} - Lumiere SPOTLIGHT OUVERTE", temps);
                    else if (debug[3])
                        Console.WriteLine("{0:hh:mm:ss.fff} - Lumiere SPOTLIGHT FERMEE", temps);
                }
            }
        }

        /// <summary>
        /// Fonction appellee lorsqu'une touche est enfoncee
        /// </summary>
        /// <param name="o"></param>
        /// <param name="e"></param>
        private void ToucheDown(Object o, KeyEventArgs e)
        {
            if ((state is TestState))
            {
                if (e.KeyCode == touches[0] && !PGJ1isPressed)
                {
                    FonctionsNatives.animerPaletteGJ1(true);
                    PGJ1isPressed = true;
                }
                if (e.KeyCode == touches[1] && !PDJ1isPressed)
                {
                    FonctionsNatives.animerPaletteDJ1(true);
                    PDJ1isPressed = true;
                }
                if (e.KeyCode == touches[4] && !ressortPressed)
                {
                    FonctionsNatives.animerRessort(true);
                    ressortPressed = true;
                }
            }
        }

        /// <summary>
        /// Fonction appeller lorsque la molette de la souris est activee
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void panel1_MouseWheel(object sender, MouseEventArgs e)
        {
            if (e.Delta < 0)
            {
                FonctionsNatives.zoomOut();
            }
            else
            {
                FonctionsNatives.zoomIn();
            }

            //panel1.Invalidate();
        }

        /// <summary>
        /// Fonction appellee lorsque la souris bouge
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void panel1_MouseMove(object sender, MouseEventArgs e)
        {
            viewState.Action(e.X, e.Y);
            if (!(state is TestState))
            {
                if (FonctionsNatives.estSelectionne() == 0)
                {
                    suprimerToolStripMenuItem.Enabled = false;
                    ribbonButtonOutilSupprimer.Enabled = false;

                }
                else
                {
                    suprimerToolStripMenuItem.Enabled = true;
                    ribbonButtonOutilSupprimer.Enabled = true;

                }

                if (state is TranslationState)
                    state.Action(e.X, e.Y);
                else if (state is RotationState || state is ScaleState)
                {
                    if (e.Button == MouseButtons.Left)
                    {
                        state.Action(e.X, e.Y);
                    }
                }
                else if (state is TranslationStateSouris)
                {
                    if (e.Button == MouseButtons.Right)
                    {
                        state.Action(e.X, e.Y);
                    }
                }
                //duplication d'objet
                else if (state is DuplicationState)
                {
                    state.Action(e.X, e.Y);
                }
                else 
                { 
                    this.DoubleBuffered = true;

                    bool test = FonctionsNatives.survolPlaque(e.X, e.Y - menuStrip1.Height - ribbon1.Height);

                    if (!test)
                    {
                        Cursor.Current = Cursors.No;
                    }
                    else
                    {
                        Cursor.Current = Cursors.Default;
                    }

                    if (state is SelectionState)
                    {
                        if (rectangleElastiqueActif && Math.Abs(positionRectangleElastiqueFinal.X - e.X) + Math.Abs(positionRectangleElastiqueFinal.Y - e.Y) > 3)
                        {
                            if (creationObjetClick != null)
                                creationObjetClick = null;
                            if (!(state is SelectionState) && !(state is ZoomState))
                            {
                                FonctionsNatives.validateMouvement();
                                FonctionsNatives.releaseVisiteurs();
                                state = new SelectionState();
                            }
                            if (positionRectangleElastiqueFinal.X != -1 && positionRectangleElastiqueFinal.Y != -1)
                                dessinerRectangleElastique(positionRectangleElastiqueFinal.X, positionRectangleElastiqueFinal.Y);
                            dessinerRectangleElastique(e.X, e.Y);
                        }
                    }
                }
            }
        }

        /// <summary>
        /// Fonction qui dessine le rectange elastique
        /// </summary>
        /// <param name="x">position en x de la souris</param>
        /// <param name="y">position en y de la souris</param>
        private void dessinerRectangleElastique(int x, int y)
        {



            if (rectangleElastique == null)
                rectangleElastique = new Rectangle();

            Point point1 = new Point(x, y);
            Point point2 = positionRectangleElastiqueInitial;

            positionRectangleElastiqueFinal = point1;

            point1 = PointToScreen(point1);
            point2 = PointToScreen(point2);
            point1.X = point1.X;
            point2.X = point2.X;
            // Normalize the rectangleElastique
            if (point1.X < point2.X)
            {
                rectangleElastique.X = point1.X;
                rectangleElastique.Width = point2.X - point1.X;
            }
            else
            {
                rectangleElastique.X = point2.X;
                rectangleElastique.Width = point1.X - point2.X;
            }
            if (point1.Y < point2.Y)
            {
                rectangleElastique.Y = point1.Y;
                rectangleElastique.Height = point2.Y - point1.Y;
            }
            else
            {
                rectangleElastique.Y = point2.Y;
                rectangleElastique.Height = point1.Y - point2.Y;
            }
            // Draw the reversible frame
            ControlPaint.DrawReversibleFrame(rectangleElastique,
                            Color.White, FrameStyle.Dashed);
        }

        /// <summary>
        /// Clique sur l'option nouveau dans le menu fichier
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void nouveauToolStripMenuItem_Click(object sender, EventArgs e)
        {
        }

        /// <summary>
        /// Clique sur l'option quitter
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void quitterToolStripMenuItem_Click(object sender, EventArgs e)
        {
        }

        /// <summary>
        /// Fonction appelle lorsqu'on clique sur le panel
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void panel1_MouseClick(object sender, MouseEventArgs e)
        {
            if (!(state is TestState))
            {
                if (state is SelectionState)
                    state.Action(e.X, e.Y);
                //duplication d'objet
                else if (state is DuplicationState)
                {
                    FonctionsNatives.validateMouvement();
                    FonctionsNatives.releaseVisiteurs();
                    state = new DuplicationState();
                }
            }
        }

        /// <summary>
        /// Les fonction suivante correspondent aux cliques de creation d'objet
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void BoutonPaletteGaucheJoueur1_Click(object sender, EventArgs e)
        {
            creationObjetClick = NOM_PALETTE_JOUEUR1_GAUCHE;
            FonctionsNatives.validateMouvement();
            FonctionsNatives.releaseVisiteurs();
            state = new AddObjectState(creationObjetClick);
            resetToolInterface();
            ribbonButtonJ1G.Checked = true;
        }

        private void BoutonPaletteDroiteJoueur1_Click(object sender, EventArgs e)
        {
            creationObjetClick = NOM_PALETTE_JOUEUR1_DROITE;
            FonctionsNatives.validateMouvement();
            FonctionsNatives.releaseVisiteurs();
            state = new AddObjectState(creationObjetClick);
            resetToolInterface();
            ribbonButtonJ1D.Checked = true;
        }

        private void BoutonPaletteGaucheJoueur2_Click(object sender, EventArgs e)
        {
            creationObjetClick = NOM_PALETTE_JOUEUR2_GAUCHE;
            FonctionsNatives.validateMouvement();
            FonctionsNatives.releaseVisiteurs();
            state = new AddObjectState(creationObjetClick);
            resetToolInterface();
            ribbonButtonJ2G.Checked = true;
        }

        private void BoutonPaletteDoiteJoueur2_Click(object sender, EventArgs e)
        {
            creationObjetClick = NOM_PALETTE_JOUEUR2_DROITE;
            FonctionsNatives.validateMouvement();
            FonctionsNatives.releaseVisiteurs();
            state = new AddObjectState(creationObjetClick);
            resetToolInterface();
            ribbonButtonJ2D.Checked = true;
        }

        private void toolStripButtonButoirCirculaire_Click(object sender, EventArgs e)
        {
            creationObjetClick = NOM_BUTOIR_CIRCULAIRE;
            FonctionsNatives.validateMouvement();
            FonctionsNatives.releaseVisiteurs();
            state = new AddObjectState(creationObjetClick);
            resetToolInterface();
            ribbonButtonBtC.Checked = true;
        }

        private void toolStripButtonCible_Click(object sender, EventArgs e)
        {
            creationObjetClick = NOM_CIBLE;
            FonctionsNatives.validateMouvement();
            FonctionsNatives.releaseVisiteurs();
            state = new AddObjectState(creationObjetClick);
            resetToolInterface();
            ribbonButtonCib.Checked = true;
        }

        private void sdToolStripMenuButoirTriangulaireGauche_Click(object sender, EventArgs e)
        {
            creationObjetClick = NOM_BUTOIR_TRIANGULAIRE_GAUCHE;
            FonctionsNatives.validateMouvement();
            FonctionsNatives.releaseVisiteurs();
            state = new AddObjectState(creationObjetClick);
            resetToolInterface();
            ribbonButtonBtG.Checked = true;
        }

        private void sdToolStripMenuItemBoutonButoirTriangulaireDroit_Click(object sender, EventArgs e)
        {
            creationObjetClick = NOM_BUTOIR_TRIANGULAIRE_DROIT;
            FonctionsNatives.validateMouvement();
            FonctionsNatives.releaseVisiteurs();
            state = new AddObjectState(creationObjetClick);
            resetToolInterface();
            ribbonButtonBtD.Checked = true;
        }

        private void toolStripButtonRessort_Click(object sender, EventArgs e)
        {
            creationObjetClick = NOM_RESSORT;
            FonctionsNatives.validateMouvement();
            FonctionsNatives.releaseVisiteurs();
            state = new AddObjectState(creationObjetClick);
            resetToolInterface();
            ribbonButtonRessort.Checked = true;
        }

        private void toolStripButtonGenerateurBille_Click(object sender, EventArgs e)
        {
            creationObjetClick = NOM_GENERATEUR_BILLE;
            FonctionsNatives.validateMouvement();
            FonctionsNatives.releaseVisiteurs();
            state = new AddObjectState(creationObjetClick);
            resetToolInterface();
            ribbonButtonGenerateur.Checked = true;
        }

        private void toolStripButtonTrou_Click(object sender, EventArgs e)
        {
            creationObjetClick = NOM_TROU;
            FonctionsNatives.validateMouvement();
            FonctionsNatives.releaseVisiteurs();
            state = new AddObjectState(creationObjetClick);
            resetToolInterface();
            ribbonButtonTro.Checked = true;
        }

        private void toolStripButtonPortail_Click(object sender, EventArgs e)
        {
            creationObjetClick = NOM_PORTAIL;
            FonctionsNatives.validateMouvement();
            FonctionsNatives.releaseVisiteurs();
            state = new AddObjectState(creationObjetClick);
            resetToolInterface();
            ribbonButtonPor.Checked = true;
        }

        private void toolStripButtonMur_Click(object sender, EventArgs e)
        {
            creationObjetClick = NOM_MUR;
            FonctionsNatives.validateMouvement();
            FonctionsNatives.releaseVisiteurs();
            state = new AddObjectState(creationObjetClick);
            resetToolInterface();
            ribbonButtonMur.Checked = true;
        }

        private void toolStripButtonDeplacer_Click(object sender, EventArgs e)
        {
            FonctionsNatives.validateMouvement();
            FonctionsNatives.releaseVisiteurs();
            state = new TranslationState();
            resetToolInterface();
            ribbonButtonBoiteOutils.Checked = true;
            ribbonButtonBoiteOutils.Image = ribbonButtonDeplacement.Image;

        }

        private void toolStripButtonRotationne_Click(object sender, EventArgs e)
        {
            FonctionsNatives.validateMouvement();
            FonctionsNatives.releaseVisiteurs();
            state = new RotationState();
            resetToolInterface();
            ribbonButtonBoiteOutils.Checked = true;
            ribbonButtonBoiteOutils.Image = ribbonButtonRotation.Image;

        }

        private void toolStripButtonMiseEchelle_Click(object sender, EventArgs e)
        {
            FonctionsNatives.validateMouvement();
            FonctionsNatives.releaseVisiteurs();
            state = new ScaleState();
            resetToolInterface();
            ribbonButtonBoiteOutils.Checked = true;
            ribbonButtonBoiteOutils.Image = ribbonButtonMiseEchelle.Image;

        }

        /// <summary>
        /// Outil duplication
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void toolStripButtonDuplication_Click(object sender, EventArgs e)
        {
            FonctionsNatives.validateMouvement();
            FonctionsNatives.releaseVisiteurs();
            state = new DuplicationState();
            ribbonButtonBoiteOutils.Image = ribbonButtonDuplication.Image;
        }

        private void toolStripButtonBille_Click(object sender, EventArgs e)
        {
            creationObjetClick = NOM_BILLE;
            FonctionsNatives.validateMouvement();
            FonctionsNatives.releaseVisiteurs();
            state = new AddObjectState(creationObjetClick);
            resetToolInterface();
        }

        /// <summary>
        /// Fonction qui s'appelle lorsqu'on appuie sur le mouse1.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void panel1_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Right)
            {
                if (viewState is ViewOrthoState)
                {
                    ((ViewOrthoState)viewState).init(e.X, e.Y);
                }
                else if (viewState is ViewPerspectiveState)
                {
                    ((ViewPerspectiveState)viewState).init(e.X, e.Y);
                }
            }

            if (!(state is TestState))
            {
                mdX = e.X;
                mdY = e.Y;

                if (state is TranslationState && FonctionsNatives.survolPlaque(e.X, e.Y))
                {
                    ((TranslationState)state).setLastPos(e.X, e.Y);
                }
                else
                {
                    positionRectangleElastiqueInitial.X = e.X;
                    positionRectangleElastiqueInitial.Y = e.Y;

                    rectangleElastiqueActif = true;
                }
                //panel1.Focus();
                //panel1.Invalidate();
            }
        }

        /// <summary>
        /// Fonction qui s'appelle lorsqu'on relache sur le mouse1.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void panel1_MouseUp(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Right)
            {
                if (viewState is ViewOrthoState)
                {
                    viewState = new ViewOrthoState();
                }
                else if (viewState is ViewPerspectiveState)
                {
                    viewState = new ViewPerspectiveState();
                }
            }

            if (!(state is TestState))
            {
                muX = e.X;
                muY = e.Y;
                if ((muY - mdY) <= 3 && (muX - mdX) <= 3)
                {
                    //Création d'un Noeud
                    if (state is AddObjectState && FonctionsNatives.survolPlaque(e.X, e.Y - menuStrip1.Height - ribbon1.Height))
                    {
                        state.Action(e.X, e.Y - menuStrip1.Height - ribbon1.Height);
                    }
                    //Selection d'objets
                    else if (state is SelectionState)
                    {
                        if ((Control.ModifierKeys & Keys.Control) == 0)
                            FonctionsNatives.deselectionnerTout();
                        FonctionsNatives.selectionSimple(e.X, e.Y, e.X, e.Y);
                        //Interface 
                        resetToolInterface();
                        ribbonButtonSelection.Checked = true;
                        //
                    }
                }
                if (state is TranslationState || state is RotationState || state is TranslationStateSouris || state is ScaleState)
                {
                    FonctionsNatives.validateMouvement();
                    FonctionsNatives.releaseVisiteurs();
                    if (state is TranslationState)
                        state = new TranslationState();
                    else if (state is RotationState)
                        state = new RotationState();
                    else if (state is TranslationStateSouris)
                        state = new SelectionState();
                }
                else if (state is ZoomState)
                {
                    if ((Control.ModifierKeys & Keys.Alt) == 0)
                        ((ZoomState)state).zoomOutRect(positionRectangleElastiqueInitial.X, positionRectangleElastiqueInitial.Y, positionRectangleElastiqueFinal.X, positionRectangleElastiqueFinal.Y);
                    else
                        ((ZoomState)state).zoomInRect(positionRectangleElastiqueInitial.X, positionRectangleElastiqueInitial.Y, positionRectangleElastiqueFinal.X, positionRectangleElastiqueFinal.Y);

                    state = new ZoomState();
                }
                else if (!(state is AddObjectState))
                {
                    //cette variable représante la distance parcourue par le pointeur entre l'évènement panel1_MouseDown et le moment actuel (l'évènement panel1_MouseUp)
                    double distanceParcourue = Math.Sqrt(Math.Pow((positionRectangleElastiqueInitial.Y - e.Y), 2.0) + Math.Pow((e.X - positionRectangleElastiqueInitial.X), 2.0));

                    if (distanceParcourue.CompareTo(3.0) == 1)
                    {

                        int gauche = Math.Min(positionRectangleElastiqueInitial.X, e.X);
                        int droite = Math.Max(positionRectangleElastiqueInitial.X, e.X);
                        int bas = Math.Min(positionRectangleElastiqueInitial.Y - menuStrip1.Height - ribbon1.Height, e.Y - menuStrip1.Height - ribbon1.Height);
                        int haut = Math.Max(positionRectangleElastiqueInitial.Y - menuStrip1.Height - ribbon1.Height, e.Y - menuStrip1.Height - ribbon1.Height);
                        if (state is SelectionState)
                        {
                            if ((Control.ModifierKeys & Keys.Control) == 0)
                                FonctionsNatives.deselectionnerTout();
                            FonctionsNatives.selectionMultiple(gauche, bas, droite, haut);
                        }
                    }
                }
                positionRectangleElastiqueInitial.X = -1;
                positionRectangleElastiqueInitial.Y = -1;
                positionRectangleElastiqueFinal.X = -1;
                positionRectangleElastiqueFinal.Y = -1;
                rectangleElastiqueActif = false;
            }
        }

        /// <summary>
        /// Fonction qui s'appelle lorsqu'on veut retourner au menu principal
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void menuPrincipalCtrlQToolStripMenuItem_Click(object sender, EventArgs e)
        {
            menu.Show();
            isActive = false;
            this.Close();
        }

        /// <summary>
        /// On enregistre la map courante
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void enregistrerToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (FonctionsNatives.estSauvegardable())
            {

                SaveFileDialog dialogueSauvegarde = new SaveFileDialog();
                dialogueSauvegarde.Title = "Sauvegarde de la zone de jeu";
                dialogueSauvegarde.Filter = "Fichier XML|*.xml";
                dialogueSauvegarde.OverwritePrompt = false;

                string initPath = Application.StartupPath + @"\zones";
                dialogueSauvegarde.InitialDirectory = initPath;
                dialogueSauvegarde.RestoreDirectory = true;

                dialogueSauvegarde.FileOk += delegate(object truc, CancelEventArgs g)
                {
                    if (Path.GetDirectoryName(dialogueSauvegarde.FileName) != dialogueSauvegarde.InitialDirectory)
                    {
                        g.Cancel = true;
                        MessageBox.Show("Mauvais dossier de sauvegarde.", "Erreur!", MessageBoxButtons.OK);
                    }
                };

                if (dialogueSauvegarde.ShowDialog() == DialogResult.OK)
                {
                    // nom entrée par l'utilisateur
                    string nomFichier = dialogueSauvegarde.FileName;

                    //chercher le nom complet du fichier XML par défaut
                    string nomChemin = dialogueSauvegarde.InitialDirectory;
                    string nomXML = nomChemin + "\\zoneDefault.xml";

                    if (nomXML != nomFichier)
                    {
                        nomFichier += "\0";
                        FonctionsNatives.ecritureXML(nomFichier.ToCharArray(0, nomFichier.Length));
                    }
                    else
                    {
                        MessageBox.Show("Impossible d'écraser le fichier XML par défaut.", "Erreur!", MessageBoxButtons.OK);
                    }

                }
            }
            else
                MessageBox.Show("L'éditeur de jeu n'a pas les objets nécessaires pour la sauvegarde.", "Erreur!", MessageBoxButtons.OK);
        }

        /// <summary>
        /// On ouvre une map
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void ouvrirToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog dialogueOuverture = new OpenFileDialog();
            dialogueOuverture.Title = "Sauvegarde de la zone de jeu";
            dialogueOuverture.Filter = "Fichier XML|*.xml";

            if (dialogueOuverture.ShowDialog() == DialogResult.OK)
            {
                string nomFichier = dialogueOuverture.FileName;

                if (nomFichier != string.Empty)
                    nomFichier += "\0";

                if (!FonctionsNatives.lireXML(nomFichier.ToCharArray(0, nomFichier.Length)))
                    MessageBox.Show("Le fichier XML est invalide.", "Erreur!", MessageBoxButtons.OK);


                //interface
                int pointsButoirCirculaire = FonctionsNatives.obtenirPointsButoirCirculaire();
                int pointsButoirTriangulaire = FonctionsNatives.obtenirPointsButoirTriangulaire();
                int pointsButoirCible = FonctionsNatives.obtenirPointsCible();
                int pointsZoneSuivante = FonctionsNatives.obtenirPointsNiveauSuivant();
                int pointsBillesBonus = FonctionsNatives.obtenirPointsBilleBonus();
                int difficulte = FonctionsNatives.obtenirDifficulteProp();
                TextBox1.TextBoxText = pointsButoirCirculaire.ToString();
                TextBox2.TextBoxText = pointsButoirTriangulaire.ToString();
                TextBox3.TextBoxText = pointsButoirCible.ToString();
                TextBox4.TextBoxText = pointsZoneSuivante.ToString();
                TextBox5.TextBoxText = pointsBillesBonus.ToString();
                comboBox1.TextBoxText = difficulte.ToString();

            }


        }
        /// <summary>
        /// Les fonctions suivantes s'occupent de l'alternance entre les differents outils d'edition
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void toolStripButtonScale_Click(object sender, EventArgs e)
        {
            FonctionsNatives.validateMouvement();
            FonctionsNatives.releaseVisiteurs();
            state = new ScaleState();
        }

        private void suprimerToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FonctionsNatives.validateMouvement();
            FonctionsNatives.releaseVisiteurs();
            state = new DeletionState();
            state.Action(0, 0);
        }

        private void toolStripZoomElastique_Click(object sender, EventArgs e)
        {
            FonctionsNatives.validateMouvement();
            FonctionsNatives.releaseVisiteurs();
            state = new ZoomState();
        }

        private void toolStripButtonSelection_Click(object sender, EventArgs e)
        {
            FonctionsNatives.validateMouvement();
            FonctionsNatives.releaseVisiteurs();
            state = new SelectionState();
            resetToolInterface();
            ribbonButtonSelection.Checked = true;


        }

        private void sélectionToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FonctionsNatives.releaseVisiteurs();
            FonctionsNatives.validateMouvement();
            state = new SelectionState();
        }

        /// <summary>
        /// Les fonctions suivante appliquent les changement a l'objet selectionne selon les options de propriete
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void textBox3_TextChanged(object sender, EventArgs e)
        {
            string valeurString;
            int valeurNum;
            valeurString = ribbonTextBoxRotation.TextBoxText;
            bool parse = Int32.TryParse(valeurString, out valeurNum);
            if (parse)
            {
                if (FonctionsNatives.estSelectionne() == 1 && (valeurNum <= 360) && (valeurNum >= 0))
                {
                    FonctionsNatives.rotationSimple(valeurNum);
                }
            }
            else if ((valeurNum >= 360) && (valeurNum <= 0))
                FonctionsNatives.rotationSimple(0);
        }

        private void textBox4_TextChanged(object sender, EventArgs e)
        {
            string valeurString;
            int valeurNum;
            valeurString = ribbonComboBoxMiseEchelle.TextBoxText;
            bool parse = Int32.TryParse(valeurString, out valeurNum);
            if (parse)
            {
                if (FonctionsNatives.estSelectionne() == 1 && (valeurNum <= 5) && (valeurNum >= 0.02))
                {
                    FonctionsNatives.miseEchelle(valeurNum);
                }
            }
            else if ((valeurNum >= 3) && (valeurNum <= 0.02))
                FonctionsNatives.miseEchelle(1);
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            string valeurString;
            int valeurNum;
            valeurString = ribbonTextBox1.TextBoxText;
            bool parse = Int32.TryParse(valeurString, out valeurNum);
            if (parse)
            {
                if (FonctionsNatives.estSelectionne() == 1)
                {
                    state = new TranslationState();
                    ((TranslationState)state).translationX(valeurNum);
                }
            }
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {
            string valeurString;
            int valeurNum;
            valeurString = ribbonTextBox2.TextBoxText;
            bool parse = Int32.TryParse(valeurString, out valeurNum);
            if (parse)
            {
                if (FonctionsNatives.estSelectionne() == 1)
                {
                    state = new TranslationState();
                    ((TranslationState)state).translationY(valeurNum);
                }
            }
        }

        /// <summary>
        /// Fonction qui s'occupe de supprimer des objets
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void ModeEditeur_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Delete)
            {
                Console.Out.WriteLine("Delete");
                state = new DeletionState();
                state.Action(0, 0);
            }
        }

        /// <summary>
        /// Creer une generateur de bille
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void générateurDeBillesToolStripMenuItem_Click(object sender, EventArgs e)
        {
            creationObjetClick = NOM_GENERATEUR_BILLE;
            FonctionsNatives.validateMouvement();
            FonctionsNatives.releaseVisiteurs();
            state = new AddObjectState(creationObjetClick);
            ribbonButtonGen.Checked = true;
        }

        /// <summary>
        /// Creer un trou
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void trouToolStripMenuItem_Click(object sender, EventArgs e)
        {
            creationObjetClick = NOM_TROU;
            FonctionsNatives.validateMouvement();
            FonctionsNatives.releaseVisiteurs();
            state = new AddObjectState(creationObjetClick);

        }

        /// <summary>
        /// Afficher l'ecran de propriete
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void propriétésToolStripMenuItem_Click(object sender, EventArgs e)
        {
            prop = new Propriete();
            prop.Show();
        }


        private void ModeEditeur_SizeChanged(object sender, EventArgs e)
        {
            FonctionsNatives.redimensionnerFenetre(this.panel1.Size.Width, this.panel1.Size.Height);
        }

        /// <summary>
        /// Changer au mode test
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void modeTestToolStripMenuItem_Click(object sender, EventArgs e)
        {
            state = new TestState();
            menuStrip1.Hide();
            ribbon1.Hide();
            // panelRotation.Hide();
        }


        /// <summary>
        /// On ferme la fenetre
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void ModeEditeur_FormClosed(object sender, FormClosedEventArgs e)
        {
            menu.Show();
        }

        /// <summary>
        /// On retourne au menu principal
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void menuPrinpalToolStripMenuItem_Click(object sender, EventArgs e)
        {
            menu.Show();
            isActive = false;
            this.Close();
        }

        /// <summary>
        /// On retourne au mode edition
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void modeÉditiontToolStripMenuItem_Click(object sender, EventArgs e)
        {
            state = new SelectionState();
            FonctionsNatives.reinitialiserPartie();
            pause = false;
            menuStrip1.Show();
            menuStrip2.Hide();
            ribbon1.Show();
            //panelRotation.Show();
        }

        private void ModeEditeur_Resize(object sender, EventArgs e)
        {
            FonctionsNatives.redimensionnerFenetre(this.panel1.Size.Width, this.panel1.Size.Height);
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void ribbonButtonVueLeft_Click(object sender, EventArgs e)
        {
            if (!(state is ViewPerspectiveState))
            {
                FonctionsNatives.translater(-1, 0);
                System.Console.WriteLine("deplacementGauche");
            }
            if (!(state is ViewOrthoState))
            {
                System.Console.WriteLine("RoationGauche");
                FonctionsNatives.rotaterXY(0.05, 0);
            }

        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void ribbonButtonVueUp_Click(object sender, EventArgs e)
        {
            if (!(state is ViewPerspectiveState))
            {
                FonctionsNatives.translater(0, 1);
                System.Console.WriteLine("deplacementHaut");
            }
            if (!(state is ViewOrthoState))
            {
                System.Console.WriteLine("RoationHaut");
                FonctionsNatives.rotaterXY(0, 0.05);
            }
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void ribbonButtonVueRight_Click(object sender, EventArgs e)
        {
            if (!(state is ViewPerspectiveState))
            {
                FonctionsNatives.translater(1, 0);
                System.Console.WriteLine("deplacementDroit");
            }
            if (!(state is ViewOrthoState))
            {
                System.Console.WriteLine("RoationDroit");
                FonctionsNatives.rotaterXY(-0.05, 0);
            }
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void ribbonButtonVueDown_Click(object sender, EventArgs e)
        {
            if (!(state is ViewPerspectiveState))
            {
                FonctionsNatives.translater(1, 0);
                System.Console.WriteLine("deplacementDroit");
            }
            if (!(state is ViewOrthoState))
            {
                System.Console.WriteLine("RoationBas");
                FonctionsNatives.rotaterXY(0, -0.05);
            }
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void ribbonButtonVueOrtho_Click(object sender, EventArgs e)
        {
            state = new ViewOrthoState();
            FonctionsNatives.changeToOrtho();
            ribbonButtonVueOrbite.Checked = false;
            ribbonButtonVueOrtho.Checked = true;
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void ribbonButtonVueOrbite_Click(object sender, EventArgs e)
        {
            state = new ViewPerspectiveState();
            FonctionsNatives.changeToPerspective();
            ribbonButtonVueOrbite.Checked = true;
            ribbonButtonVueOrtho.Checked = false;
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void ribbonButtonZoomIn_Click(object sender, EventArgs e)
        {
            FonctionsNatives.zoomIn();
            System.Console.WriteLine("ZoomIn");

        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void ribbonButtonZoomOut_Click(object sender, EventArgs e)
        {
            FonctionsNatives.zoomOut();
            System.Console.WriteLine("ZoomOut");
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void ribbonPanelOutilsF_ButtonMoreClick(object sender, EventArgs e)
        {

        }



        private void resetToolInterface()
        {
            ribbonButtonBoiteOutils.Image = ribbonButtonBoiteOutils.SmallImage;
            ribbonButtonSelection.Checked = false;
            ribbonButtonBoiteOutils.Checked = false;
            foreach (RibbonButton buttonObjet in ribbonButtonListObjets.Buttons)
            {
                buttonObjet.Checked = false;
            }

        }

        private void ribbonButtonListObjets_ButtonItemClicked(object sender, RibbonItemEventArgs e)
        {
            resetToolInterface();
        }


        private void ribbonButton7_Click(object sender, EventArgs e)
        {
            int pointsButoirCirculaire = FonctionsNatives.obtenirPointsButoirCirculaire();
            int pointsButoirTriangulaire = FonctionsNatives.obtenirPointsButoirTriangulaire();
            int pointsButoirCible = FonctionsNatives.obtenirPointsCible();
            int pointsZoneSuivante = FonctionsNatives.obtenirPointsNiveauSuivant();
            int pointsBillesBonus = FonctionsNatives.obtenirPointsBilleBonus();
            int difficulte = FonctionsNatives.obtenirDifficulteProp();
            bool valider1 = false, valider2 = false, valider3 = false, valider4 = false, valider5 = false;


            string valeurString;
            double valeurNumDouble;
            int valeurNum;

            //validation butoir circulaire
            valeurString = TextBox1.TextBoxText;
            bool parse = Double.TryParse(valeurString, out valeurNumDouble);
            if (parse)
            {
                if (valeurNumDouble >= 1 && valeurNumDouble <= 500)
                {
                    valeurNum = Convert.ToInt32(valeurNumDouble);
                    pointsButoirCirculaire = valeurNum;
                    valider1 = true;
                }
                else
                {
                    MessageBox.Show("Erreur, entree invalide pour butoir circulaire");
                    pointsButoirCirculaire = 10;
                    valider1 = false;
                }
            }
            else
            {
                MessageBox.Show("Erreur, entree invalide pour butoir circulaire");
                pointsButoirCirculaire = 10;
                valider1 = false;
            }

            //validation butoir triangulaire
            valeurString = TextBox2.TextBoxText;
            parse = Double.TryParse(valeurString, out valeurNumDouble);
            if (parse)
            {
                if (valeurNumDouble >= 1 && valeurNumDouble <= 500)
                {
                    valeurNum = Convert.ToInt32(valeurNumDouble);
                    pointsButoirTriangulaire = valeurNum;
                    valider2 = true;
                }
                else
                {
                    MessageBox.Show("Erreur, entree invalide pour butoir triangulaire");
                    pointsButoirTriangulaire = 10;
                    valider2 = false;
                }
            }
            else
            {
                MessageBox.Show("Erreur, entree invalide pour butoir triangulaire");
                pointsButoirTriangulaire = 10;
                valider2 = false;
            }

            //Validation cible
            valeurString = TextBox3.TextBoxText;
            parse = Double.TryParse(valeurString, out valeurNumDouble);
            if (parse)
            {
                if (valeurNumDouble >= 1 && valeurNumDouble <= 500)
                {
                    valeurNum = Convert.ToInt32(valeurNumDouble);
                    pointsButoirCible = valeurNum;
                    valider3 = true;
                }
                else
                {
                    MessageBox.Show("Erreur, entree invalide pour cible");
                    pointsZoneSuivante = 1000;
                    valider3 = false;
                }
            }
            else
            {
                MessageBox.Show("Erreur, entree invalide pour cible");
                pointsZoneSuivante = 1000;
                valider3 = false;
            }

            //Validation points victoire
            valeurString = TextBox4.TextBoxText;
            parse = Double.TryParse(valeurString, out valeurNumDouble);
            if (parse)
            {
                if (valeurNumDouble >= 100 && valeurNumDouble <= 10000)
                {
                    valeurNum = Convert.ToInt32(valeurNumDouble);
                    pointsZoneSuivante = valeurNum;
                    valider4 = true;
                }
                else
                {
                    MessageBox.Show("Erreur, entree invalide pour points victoire");
                    pointsZoneSuivante = 1000;
                    valider4 = false;
                }
            }
            else
            {
                MessageBox.Show("Erreur, entree invalide pour points victoire");
                pointsZoneSuivante = 1000;
                valider4 = false;
            }


            //validation  des points bille gratuite
            valeurString = TextBox5.TextBoxText;
            parse = Double.TryParse(valeurString, out valeurNumDouble);
            if (parse)
            {
                if (valeurNumDouble >= 50 && valeurNumDouble <= 2000)
                {
                    valeurNum = Convert.ToInt32(valeurNumDouble);
                    pointsBillesBonus = valeurNum;
                    valider5 = true;
                }
                else
                {
                    MessageBox.Show("Erreur, entree invalide pour bille gratuite");
                    pointsBillesBonus = 200;
                    valider5 = false;
                }
            }
            else
            {
                MessageBox.Show("Erreur, entree invalide pour bille gratuite");
                pointsBillesBonus = 200;
                valider5 = false;
            }

            // confirmation difficulte
            difficulte = Convert.ToInt32(comboBox1.TextBoxText);

            // confirmation et assignation
            if (valider1 && valider2 && valider3 && valider4 && valider5)
            {
                FonctionsNatives.assignerPointsButoirTriangulaire(pointsButoirTriangulaire);
                FonctionsNatives.assignerPointsButoirCirculaire(pointsButoirCirculaire);
                FonctionsNatives.assignerPointsCible(pointsButoirCible);
                FonctionsNatives.assignerPointsNiveauSuivant(pointsZoneSuivante);
                FonctionsNatives.assignerPointsBilleBonus(pointsBillesBonus);
                FonctionsNatives.assignerDifficulte(difficulte);
                MessageBox.Show("OK");
            }
            else
                MessageBox.Show("Erreur, une des entrees n'est pas valider");


        }

        private void ribbonTabConfig_ActiveChanged(object sender, EventArgs e)
        {


        }

        private void panel1_Paint(object sender, PaintEventArgs e)
        {

        }

        private void orthographiqueToolStripMenuItem_Click(object sender, EventArgs e)
        {
            viewState = new ViewOrthoState();
            FonctionsNatives.changeToOrtho();
        }

        private void orbiteToolStripMenuItem_Click(object sender, EventArgs e)
        {
            viewState = new ViewPerspectiveState();
            FonctionsNatives.changeToPerspective();
        }

        private void orthographiqueToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            viewState = new ViewOrthoState();
            FonctionsNatives.changeToOrtho();
        }

        private void orbiteToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            viewState = new ViewPerspectiveState();
            FonctionsNatives.changeToPerspective();
        }
    }
    static partial class FonctionsNatives
    {
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void initialiserOpenGL(IntPtr handle);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void libererOpenGL();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void dessinerOpenGL();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void animer(double temps);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void selectionSimple(int left, int top, int right, int bottom);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void RetournerPosition(int x, int y);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void deselectionnerTout();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void selectionMultiple(int gauche, int haut, int droite, int bas);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ajouterNoeudMur(int x1, int y1, int x2, int y2);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool survolPlaque(int x, int y);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool releaseVisiteurs();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool validateMouvement();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ecritureXML(char[] nomFichier);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool lireXML(char[] nomFichier);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool estSauvegardable();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int estSelectionne();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void rotationSimple(double angle);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void miseEchelle(double scale);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void changerPoints(int points, char[] nom);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void changerDifficulte(int points, string nom);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void changerPointsCampage(int points);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void changerPointsBille(int points);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zoomIn();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zoomOut();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void translater(double deplacementX, double deplacementY);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void redimensionnerFenetre(int largeur, int hauteur);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void reinitialiser();
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void animerPaletteGJ1(bool sons);
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void animerPaletteGJ2(bool sons);
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void animerPaletteDJ1(bool sons);
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void animerPaletteDJ2(bool sons);
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void animerRessort(bool animer);
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void reinitialiserPartie();
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void assignerDebug(bool[] dbug);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void rotaterXY(double rotationX, double rotationY);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void changeToOrtho();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void changeToPerspective();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void changeLumAmbiant();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void changeLumDirect();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void changeLumSpot();
    }
}
