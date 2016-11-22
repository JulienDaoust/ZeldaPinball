using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace InterfaceGraphique
{
    public partial class PartieCampagne : Form
    {

        ConfigurationPartie configCampagne_;
        
        public PartieCampagne(ConfigurationPartie config)
        {
            InitializeComponent();
            //InitialiserAnimation();
            configCampagne_ = config;
            //chargerZone(configCampagne_.zones_[0]);
            chargerProchaineZone();
            this.Hide();
        }

        public void MettreAJour(double tempsInterAffichage)
        {
            try
            {
                this.Invoke((MethodInvoker)delegate
                {
                    
                    int etatActuel = etatZoneActuelle();
                    //si la zone est réussi
                    if (etatActuel == 1)
                    {
                        //Vérifie si il reste encore des zones a jouer dans la campagne
                        if (configCampagne_.indiceZoneActuel_ < configCampagne_.quantiteZones_)
                        {
                            chargerProchaineZone();
                        }
                        else 
                        {
                            //Campagne termine
                            //afficher un message de victoire: réussi ce niveau
                            var result = MessageBox.Show("Voulez vous rejouer cette campagne? ", "Félicitation! Vous avez terminé la Campagne. ", MessageBoxButtons.YesNo);
                            //si l'utilisateur décide de rejouer, on 
                            if (result == DialogResult.Yes)
                            {
                                libererZoneActuel();
                                chargerZone(configCampagne_.zones_[0]);
                            }
                            else
                                this.Close();
                        }

                    }
                    //si la zone est échoué
                    else if (etatActuel == -1) 
                    {
                        //Campagne termine (echec)
                        var result = MessageBox.Show("Voulez vous rejouer cette campagne? ", "Échec! Vous avez perdu. ", MessageBoxButtons.YesNo);
                        //si l'utilisateur décide de rejouer, on 
                        if (result == DialogResult.Yes)
                        {
                            libererZoneActuel();
                            chargerZone(configCampagne_.zones_[0]);
                        }
                        else
                            this.Close();
                    }
                    
                    //si la zone n'est pas terminé: continue

                    FonctionsNatives.animer(tempsInterAffichage);
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

            FonctionsNatives.reinitialiser();
            //charge l'arbre
            if (!FonctionsNatives.lireXML(zone.path_.ToCharArray(0, zone.path_.Length)))
            {
                MessageBox.Show("La zone par défaut seras chargé ", "Zone de jeux inexistante!", MessageBoxButtons.OK);
                string zoneDefault = Application.StartupPath + @"\zones\default.xml\0";
                if (!FonctionsNatives.lireXML(zoneDefault.ToCharArray(0, zoneDefault.Length)))
                {
                    MessageBox.Show("Probleme avec la zoneDefault. La prochaine zone seras chargé", "Zone par défault introuvalbe!", MessageBoxButtons.OK);
                    chargerProchaineZone();
                }
            }
            //initialise le nombre de billes dans l'arbre
            FonctionsNatives.assignerNbBillesInitial(configCampagne_.billesInitialles_);

            //afficher message avec le nom de la map pendent 5 sec (permetre a l'utilisateur de skipper avec espace)
            //TODO:: timer wait 5 sec
             

        }

        /// <summary>
        /// Cette méthode libre la zone présentement  utilisée
        /// 
        /// </summary>
        private void libererZoneActuel()
        {
            FonctionsNatives.libererOpenGL();
           // FonctionsNatives.reinitialiser();
            InitialiserAnimation();
        }

        /// <summary>
        /// cette méthode passe a la prochaine zone
        /// </summary>
        private void chargerProchaineZone() 
        {
            /*
            libererZoneActuel();
            configCampagne_.indiceZoneActuel_++;
            chargerZone(configCampagne_.zones_[configCampagne_.indiceZoneActuel_]);
            */

            //logique a la david gourde
            
           
            
            Program.partieRapide = new PartieRapide(configCampagne_);
            if(Program.partieRapide != null)
             Program.partieRapide.Show();

            configCampagne_.indiceZoneActuel_++;
            
            
        }


        /// <summary>
        /// cette méthode vérifie l'état de la zone actuel
        /// elle vérifie si la partieRapide en cours est terminé 
        /// </summary>
        /// <returns>
        /// 1 si est termine avec succes
        /// -1 termine avec echec
        /// 0 si non terminé
        /// </returns>
        private int etatZoneActuelle()
        {
            //Verifie si la partieRapide est perdue
            /*
            if (FonctionsNatives.obtenirNbBillesActuel() <= 0)
            {

                return -1;
            }
            //Verifie si on a atein le pointage seuil necessaire pour terminer la ZoneActuelle
            if (FonctionsNatives.obtenirPointageActuel() >= configCampagne_.zones_[configCampagne_.indiceZoneActuel_].pointsSeuil_)
            {
                return 1;
            }
            */

            //Logique GOURDE!!!
            if (Program.partieRapide == null)
                return -1;

            return 0;
        }

        public void InitialiserAnimation()
        {
            this.DoubleBuffered = true;
            FonctionsNatives.initialiserOpenGL(panel1.Handle);
            FonctionsNatives.dessinerOpenGL();
        }

        private void PartieCampagne_FormClosed(object sender, System.Windows.Forms.FormClosedEventArgs e)
        {
            //TODO:: problems HERE too!!!!!!
            FonctionsNatives.releaseVisiteurs();
            FonctionsNatives.libererOpenGL();
            //FonctionsNatives.reinitialiser();
           
            Program.menuPrincipal.Show();
            this.Dispose();
        }

        private void menuPrincipalToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void nextZoneToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //TODO: enlever cette méthode et l'option menu associé
            chargerProchaineZone();
        }
    }
}
