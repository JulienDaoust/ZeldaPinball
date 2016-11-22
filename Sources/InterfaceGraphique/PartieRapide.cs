using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using InterfaceGraphique.patron_state;

namespace InterfaceGraphique
{
    public partial class PartieRapide : Form
    {
        //Configuration de partie/campagne
        ConfigurationPartie configSimple_;
        //Zone dans laquelle la partie est joué
        ZoneDeJeux zone_;

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
        //touches configurées par l'utilisateur
        Keys[] touches = new Keys[5];
        //Savoir si on est mode debug pour les lumieres
        bool debugLum = false;
        //Lumiere ambiante
        bool lumAmbiante = false;
        //Lumiere directionnelle
        bool lumDirect = false;
        //Spotlights
        bool spotlights = false;
        /// <summary>
        /// la variable d'état de la vue
        /// </summary>
        AbstractState viewState = new ViewPerspectiveState();
        Boolean isActive = true;

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

        public PartieRapide(ZoneDeJeux zone, ConfigurationPartie config)
        {
            FonctionsNatives.reinitialiser();
            this.MouseWheel += new MouseEventHandler(panel1_MouseWheel);
            InitializeComponent();
            InitialiserAnimation();
            configSimple_ = config;
            zone_ = zone;
            FonctionsNatives.affichageTexte();
            InitialiserZone();
            panel2.Size = new System.Drawing.Size(1214, 753);     
        }
        /// <summary>
        /// Cette méthode est responsable d'initialiser la zone et d'appliquer 
        /// les conficuration nessesaires
        /// </summary>
        private void InitialiserZone() 
        {
            //touches
            this.KeyDown += new KeyEventHandler(ToucheDown);
            this.KeyUp += new KeyEventHandler(ToucheUp);
            recupererTouches();

            //Chargement de la zone
            chargerZone(zone_);
            //Configure le jouer virtuelle dans le modele
            FonctionsNatives.assignerJoueurVirtuel(configSimple_.joueurVirtuel_);
            //Obtenir le nombre de points de la zone actuel a partir du modelle
            zone_.pointsSeuil_ = FonctionsNatives.obtenirPointsNiveauSuivant();

            //configure l'info d'affichage (désuet)
            this.Text = zone_.nom_;
            
            
        }
        private void ToucheUp(Object o, KeyEventArgs e)
        {
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

            if (e.KeyCode == touches[2] && PGJ2isPressed && configSimple_.estMultiplayer_ && !configSimple_.joueurVirtuel_)
            {
                 FonctionsNatives.animerPaletteGJ2(false);
                 PGJ2isPressed = false;
            }

            if (e.KeyCode == touches[3] && PDJ2isPressed && configSimple_.estMultiplayer_ && !configSimple_.joueurVirtuel_)
            {
                 FonctionsNatives.animerPaletteDJ2(false);
                 PDJ2isPressed = false;
            }
            if (e.KeyCode == touches[4] && ressortPressed)
            {
                FonctionsNatives.animerRessort(false);
                ressortPressed = false;
            }

            if (e.KeyValue == (char)Keys.Back)
            {
                recupererTouches();
                FonctionsNatives.reinitialiserPartie();
            }

            if (e.KeyCode == Keys.J)
            {
                lumAmbiante = !lumAmbiante;
                FonctionsNatives.changeLumAmbiant();
                DateTime temps = DateTime.Now;
                if (lumAmbiante && debugLum)
                    Console.WriteLine("{0:hh:mm:ss.fff} - Lumiere AMBIANTE OUVERTE", temps);
                else if(debugLum)
                    Console.WriteLine("{0:hh:mm:ss.fff} - Lumiere AMBIANTE FERMEE", temps);
            }
            if (e.KeyCode == Keys.K )
            {
                lumDirect = !lumDirect;
                FonctionsNatives.changeLumDirect();
                DateTime temps = DateTime.Now;
                if (lumDirect && debugLum)
                    Console.WriteLine("{0:hh:mm:ss.fff} - Lumiere DIRECTIONELLE OUVERTE", temps);
                else if(debugLum)
                    Console.WriteLine("{0:hh:mm:ss.fff} - Lumiere DIRECTIONELLE FERMEE", temps);
            }
            if (e.KeyCode == Keys.L )
            {
                spotlights = !spotlights;
                FonctionsNatives.changeLumSpot();
                DateTime temps = DateTime.Now;
                if (spotlights && debugLum)
                    Console.WriteLine("{0:hh:mm:ss.fff} - Lumiere SPOTLIGHT OUVERTE", temps);
                else if(debugLum)
                    Console.WriteLine("{0:hh:mm:ss.fff} - Lumiere SPOTLIGHT FERMEE", temps);
            }
        }

        private void ToucheDown(Object o, KeyEventArgs e)
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

            if (e.KeyValue == (char)Keys.Escape && pause == false)
            {
                pause = true;
                menuStrip1.Show();
                e.Handled = true;
                FonctionsNatives.pauserSon();
            }
            if (e.KeyValue == (char)Keys.Escape && pause == true && e.Handled == false)
            {
                pause = false;
                menuStrip1.Hide();
                e.Handled = true;
                FonctionsNatives.pauserSon();
            }

           
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


            if (e.KeyCode == touches[2] && !PGJ2isPressed && configSimple_.estMultiplayer_ && !configSimple_.joueurVirtuel_)
            {
                FonctionsNatives.animerPaletteGJ2(true);
                
                PGJ2isPressed = true;
            }


            if (e.KeyCode == touches[3] && !PDJ2isPressed && configSimple_.estMultiplayer_ && !configSimple_.joueurVirtuel_)
            {
                FonctionsNatives.animerPaletteDJ2(true);
                
                PDJ2isPressed = true;
            }
            

            if (e.KeyCode == touches[4] && !ressortPressed)
            {
                
                FonctionsNatives.animerRessort(true);
                ressortPressed = true;
            }
      
        }
        public void MettreAJour(double tempsInterAffichage)
        {
            try
            {
                if(isActive)
                   FonctionsNatives.redimensionnerFenetre(panel2.Width, panel2.Height);
                this.Invoke((MethodInvoker)delegate
                {
                    //si la zone est réussi
                    if (FonctionsNatives.victoire()==1)
                    {
                        this.DialogResult = DialogResult.OK;
                        FonctionsNatives.desactiverSon();
                        FonctionsNatives.libererOpenGL();
                        isActive = false;
                        this.Close();
                    }
                    //si la zone est échoué
                    else if (FonctionsNatives.gameOver()==1) 
                    {
                         this.DialogResult = DialogResult.No;
                         FonctionsNatives.desactiverSon();
                         FonctionsNatives.libererOpenGL();
                         isActive = false; 
                        this.Close();
                    }

                   
                    if (!pause)
                    {
                        FonctionsNatives.animer(tempsInterAffichage);
                    }
                    FonctionsNatives.dessinerOpenGL();
                });
            }
            catch (Exception)
            {
            }

        }

        /// <summary>
        /// Cette methode configure la Campagne selon la configuration de partieRapide
        /// recu en parametre
        /// 
        /// </summary>
        /// <param name="config">configuration qui inclus  tout ce que la campagne 
        /// a besoin pour se configurer</param>
        /// 
        /// <returns></returns>
        private void chargerZone(ZoneDeJeux zone)
        {
            //initialise l'arbre
            if (!FonctionsNatives.lireXML(zone.path_.ToCharArray(0, zone.path_.Length)))
            {
                MessageBox.Show("La zone par défaut seras chargé ", "Zone de jeux inexistante!", MessageBoxButtons.OK);
                string zoneDefault = Application.StartupPath + @"\zones\default.xml"+"\0";
                if (!FonctionsNatives.lireXML(zoneDefault.ToCharArray(0, zoneDefault.Length)))
                {
                    MessageBox.Show("Probleme avec la zoneDefault", "Zone par défault introuvalbe!", MessageBoxButtons.OK);
                    FonctionsNatives.desactiverSon();
                    panel2.SetBounds(panel2.Bounds.X, panel2.Bounds.Y, 1214, 753, BoundsSpecified.Location);
                    this.Close();
                }
               
            }

            //initialise le nombre de billes dans l'arbre
            FonctionsNatives.assignerNbBillesInitial(configSimple_.billesInitialles_);
            //initialise points Zone Suivante dans l'arbre

        }

     public void InitialiserAnimation()
     {
         this.DoubleBuffered = true;
         FonctionsNatives.initialiserOpenGL(panel2.Handle);
         FonctionsNatives.dessinerOpenGL();
     }
     private void menuPrincipalToolStripMenuItem_Click(object sender, EventArgs e)
     {
         this.DialogResult = DialogResult.No;
         Program.menuPrincipal.Show();
         FonctionsNatives.desactiverSon();
         FonctionsNatives.affichageTexte();
         panel2.SetBounds(panel2.Bounds.X, panel2.Bounds.Y, 1214, 753, BoundsSpecified.Location);
         this.Close();
     }


     private void recupererTouches()
     {
         string pathConfig = Application.StartupPath + "/données/Config.txt";
         string[] touche = System.IO.File.ReadAllLines(pathConfig);
         touches[0] = (Keys)Enum.Parse(typeof(Keys), touche[0]);
         touches[1] = (Keys)Enum.Parse(typeof(Keys), touche[1]);

         touches[2] = (Keys)Enum.Parse(typeof(Keys), touche[2]);
         touches[3] = (Keys)Enum.Parse(typeof(Keys), touche[3]);
        
         touches[4] = (Keys)Enum.Parse(typeof(Keys), touche[4]);
         FonctionsNatives.assignerBillesRestantes(Convert.ToInt32(touche[5]));
         
         if (touche[6].ToString() == "Activer")
             FonctionsNatives.assignerBillesMax(2);
         else
             FonctionsNatives.assignerBillesMax(1);

         if (touche[7].ToString() == "Activer")
             FonctionsNatives.assignerAffichageDebug(true);
         else
             FonctionsNatives.assignerAffichageDebug(false);

         if (touche[8].ToString() == "Oui")
             FonctionsNatives.assignerAffichageCreationBille(true);
         else
             FonctionsNatives.assignerAffichageCreationBille(false);

         if (touche[9].ToString() == "Oui")
             FonctionsNatives.assignerAffichageVitesse(true);
         else
             FonctionsNatives.assignerAffichageVitesse(false);

         if (touche[11].ToString() == "Oui")
             FonctionsNatives.assignerAffichagePortail(true);
         else
             FonctionsNatives.assignerAffichagePortail(false);
         if (touche[10].ToString() == "Oui" && touche[7].ToString() == "Activer")
             debugLum = true;
         else
             debugLum = false;
     }
    
     private void partieSimpleClosed(object sender, FormClosedEventArgs e)
     {
         Program.menuPrincipal.Show();
         FonctionsNatives.desactiverSon();
         FonctionsNatives.affichageTexte();
         panel2.SetBounds(panel2.Bounds.X, panel2.Bounds.Y, 1214, 753, BoundsSpecified.Location);
         this.Close();
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

     private void panel1_mouseDown(object sender, MouseEventArgs e)
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
     }

     private void panel1_mouseMove(object sender, MouseEventArgs e)
     {
         viewState.Action(e.X, e.Y);
     }

     private void panel1_mouseUp(object sender, MouseEventArgs e)
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
     }

     private void orthographiqueToolStripMenuItem_Click(object sender, EventArgs e)
     {
         viewState = new ViewPerspectiveState();
         FonctionsNatives.changeToPerspective();
     }

     private void orbiteToolStripMenuItem_Click(object sender, EventArgs e)
     {
         viewState = new ViewOrthoState();
         FonctionsNatives.changeToOrtho();
     }

    }


    static partial class FonctionsNatives
    {

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void assignerNbBillesInitial(int nbBilles);
    
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void assignerJoueurVirtuel(bool estJoueurVirtuel);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int obtenirNbBillesActuel();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int obtenirPointageActuel();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int assignerBillesRestantes(int bille);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int assignerBillesMax(int bille);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int assignerAffichageDebug(bool actif);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int assignerAffichageVitesse(bool actif);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int assignerAffichageCreationBille(bool actif);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int assignerAffichagePortail(bool actif);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int gameOver();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int victoire();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void activerSonBackground();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void desactiverSon();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void pauserSon();

    }
}
