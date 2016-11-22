using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using System.IO;
using System.Collections;

namespace InterfaceGraphique
{
    /// <summary>
    /// Interface qui gere la campagne et ses configurations
    /// </summary>
    public partial class MenuCampagne : Form
    {

        //configurations de la campagne
        ConfigurationPartie configCampagne;
        //Liste avec tout les zones
        public List<ZoneDeJeux> zones_;
        //Écran de chargement
        LoadScreen loadScreen;

        //Redefinition d'un item de ComboBox
        public class ComboBoxItem
        {
            public string Text { get; set; }
            public string Value { get; set; }
            public int Difficulte;

            public override string ToString() { return Text; }
        }

        public MenuCampagne()
        {
            InitializeComponent();
            configCampagne = new ConfigurationPartie();
            zones_ = new List<ZoneDeJeux>();
            recupererCampagneEnregistre();
            chargerZonesDisponibles();
        }

        /// <summary>
        /// Cette méthode recois un fichier et détermine si son extension est .XML
        /// </summary>
        /// <param name="path">chemin vers le fichier</param>
        /// <returns>nom du fichier</returns>
        private string getNomXML(string path)
        {

                string nomFichier = Path.GetFileName(path);

                //separe le nom(nomEtEtention[0]) et l'extention du fichier(nomEtEtention[1])
                string[] nomEtExtention = nomFichier.Split('.');
                if(nomEtExtention.Length == 2)
                {
                    if (String.Compare(nomEtExtention[1], "xml", true) == 0)
                        /// retourne la partie correspondente au nom sans l'extention
                        return nomEtExtention[0];
                }
                else 
                {
                    MessageBox.Show("Problem avec le nom de la partie! Le fichier n'est pas un xml");
                }
            
            return "pasXML";
        }

        /// <summary>
        /// charge une zone dans le combo box
        /// </summary>
        /// <param name="path">ptah de la zone</param>
        private ComboBoxItem chargerZone(string path, string nomFichier)
        {
            string pathAbsolut =Application.StartupPath + @"\zones\" + path;
            //si la zone existe charger zone 
            if (File.Exists(pathAbsolut))
            {
                if (pathAbsolut != string.Empty)
                    pathAbsolut += "\0";

                int difficulte = FonctionsNatives.obtenirDifficulte(pathAbsolut.ToCharArray(0, pathAbsolut.Length));
                ComboBoxItem zoneValide = new ComboBoxItem();
                zoneValide.Text = nomFichier + "(" + difficulte + ")";
                zoneValide.Value = path;
                zoneValide.Difficulte = difficulte;
                return zoneValide;
            }
            //pour le chargement de la campagne entérieur
            //loader default.xml si la zone n'est pas dans le fichier
            else 
            {
                pathAbsolut = Application.StartupPath + @"\zones\default.xml";
                string nomFichierDefault = getNomXML(pathAbsolut);
                if (pathAbsolut != string.Empty)
                    pathAbsolut += "\0";
                
                int difficulte = FonctionsNatives.obtenirDifficulte(pathAbsolut.ToCharArray(0, pathAbsolut.Length));

                ComboBoxItem zoneDefault = new ComboBoxItem();
                zoneDefault.Text = nomFichierDefault + "(:" + difficulte + ")";
                zoneDefault.Value = "default.xml";
                zoneDefault.Difficulte = difficulte;
                return zoneDefault;
            }
        }
        /// <summary>
        /// configure le comboBoxZones pour offir le choix des Zones disponibles dans le fichier Zones
        /// 
        /// on vas chercher tout les fichier .xml qui sont dans ...\zones\ et on les liste dans le comboBox
        /// /TODO
        /// </summary>
        private void chargerZonesDisponibles()
        {
            
            string pathAbsolut = Application.StartupPath + @"\zones";         

            //getFile retourne un tableau avec le path de tout les fichiers
            foreach (string path in Directory.GetFiles(pathAbsolut))
            {
                string nomFichier = getNomXML(path);
                string pathRelatif = Path.GetFileName(path);

                if (nomFichier != "pasXML")
                {
                    comboBoxZones.Items.Add(chargerZone(pathRelatif, nomFichier));
                }
            }
        }

        private void buttonDemarer_Click(object sender, EventArgs e)
        {
            enregistrerCampagneActuel();

            //chargement des zones choisies 
            foreach (ComboBoxItem item in listBoxZones.Items)
            {
                string localPath = Application.StartupPath + @"\zones\" + item.Value;
                if (localPath != string.Empty)
                    localPath += "\0";

                //configCampagne.ajouterZone(item.Value, item.ToString(), item.Difficulte);
                ajouterZone(localPath, item.ToString(), item.Difficulte);
            }
            ordonnerParDifficulte();

            demarerCampagne();
        }

        /// <summary>
        /// cette méthode joue les partie de la campagne une a une
        /// </summary>
        private void demarerCampagne()
        {
            this.Hide();
            var resultatPartie = DialogResult.Retry;
            for (int i = 0; i < zones_.Count && resultatPartie != DialogResult.No; i++)
            {
                
                //chargement de la partie
                Program.partieRapide = new PartieRapide(zones_[i], configCampagne);
                //fenetre de chargement de la partie
                loadScreen = new LoadScreen(zones_[i]);
                loadScreen.ShowDialog();
                FonctionsNatives.activerSonBackground();
                //affichage de la partie
                resultatPartie = Program.partieRapide.ShowDialog();
                this.Hide();
            }

            var resultatRejouer = DialogResult.Retry;
            //si la partie est perdue
            if (resultatPartie == DialogResult.No)
            {
                resultatRejouer = MessageBox.Show("Voulez vous rejouer cette campagne? ", " Vous avez perdu! ", MessageBoxButtons.YesNo);
            }
            //Si la dernierre zone est réussi
            else if (resultatPartie == DialogResult.OK)
            {
                resultatRejouer = MessageBox.Show("Voulez vous rejouer cette campagne? ", " Vous avez réussi la Campagne. ", MessageBoxButtons.YesNo);
            }

            if (resultatRejouer == DialogResult.Yes)
                demarerCampagne();
            else
                Program.menuPrincipal.Show();
            
            
        }


        /// <summary>
        /// Méthode ajoute une zone a la liste de zones
        /// </summary>
        /// <param name="fichierChoisi"></param>
        /// <param name="nom"></param>
        /// <param name="dificulte"></param>
        public void ajouterZone(string fichierChoisi, string nom, int dificulte)
        {
            ZoneDeJeux zoneRapide = new ZoneDeJeux(fichierChoisi, nom, dificulte);
            zones_.Add(zoneRapide);
            //quantiteZones_++;
        }

        /// <summary>
        ///Odenne les zones en ordre de dificulté
        /// </summary>
        /// <param name="pathFichier"></param>
        /// <param name="nomFichier"></param>
        /// <param name="dificulte"></param>
        /// <param name="quantiteZones"></param>
        public void ordonnerParDifficulte()
        {
            zones_.Sort();
        }
        private void buttonAnuler_Click(object sender, EventArgs e)
        {
            this.Close();
            Program.menuPrincipal.Show();
        }

        private void ConfigurationCampagne_FormClosed(object sender, FormClosedEventArgs e)
        {
            Program.menuPrincipal.Show();
            this.Dispose();
        }

        private void buttonSuprimer_Click(object sender, EventArgs e)
        {
            listBoxZones.Items.Clear();
            buttonDemarer.Enabled = false;
        }

        private void buttonSuprimer1_Click(object sender, EventArgs e)
        {
            listBoxZones.Items.Remove(listBoxZones.SelectedItem);
            if (listBoxZones.Items.Count < 2)
                buttonDemarer.Enabled = false;

        }

        private void radioVirtuel_CheckedChanged(object sender, EventArgs e)
        {
            configCampagne.joueurVirtuel_ = true;
        }

        private void radioSinglePlayer_CheckedChanged(object sender, EventArgs e)
        {
            configCampagne.estMultiplayer_ = false;
            groupBoxDeuxiemmeJoueur.Visible = false;
            //radioButtonHumain.Checked = true;
        }

        private void radioButtonCoop_CheckedChanged(object sender, EventArgs e)
        {
            configCampagne.estMultiplayer_ = true;
            groupBoxDeuxiemmeJoueur.Visible = true;
        }

        private void radioButtonHumain_CheckedChanged(object sender, EventArgs e)
        {
            configCampagne.joueurVirtuel_ = false;
            //groupBoxDeuxiemmeJoueur.Visible = true;
        }

        private void comboBoxZones_SelectionChangeCommitted_1(object sender, EventArgs e)
        {
            listBoxZones.Items.Add(comboBoxZones.SelectedItem);

            //Verifier si il y a au moin 2 zones avant de Demarer
            if (listBoxZones.Items.Count >= 2)
                buttonDemarer.Enabled = true;
        }

        /// <summary>
        /// recupere la campagne enregistrée dans le fichjier config.txt
        /// 
        /// </summary>
        private void recupererCampagneEnregistre()
        {
            string pathConfig = Application.StartupPath + "/données/Config.txt";
            string[] fichierConfig = System.IO.File.ReadAllLines(pathConfig);
            
            //si il existe une configuration enrregistré dans le fichier de config
            if(fichierConfig.Length > 12 )
            {
                if (fichierConfig[12] != String.Empty)
                {
                    //met charque partie dans 
                    for (int i = 12; i < fichierConfig.Length; i++)
                    {
                        //met le fichier dans la liste
                        string path = fichierConfig[i];
                        //enleve l'espace de la fin
                        //path.TrimEnd();
                        string nomFichier = getNomXML(path);
                        //insere charge la zone dans le listBox
                        listBoxZones.Items.Add(chargerZone(path, nomFichier));
                    }
                }
            }

            //active le bouton de démarer si il y a plus que 2 partie
            if (listBoxZones.Items.Count >= 2)
                buttonDemarer.Enabled = true;
        }

        /// <summary>
        /// Cette méthode cas chercher les items qui sont dans la listBox et les 
        /// erregistre a la fin du fichier de configurations
        /// 
        /// 
        /// </summary>
        private void enregistrerCampagneActuel() 
        {
            string pathConfig = Application.StartupPath + "/données/Config.txt";
            string[] fichierConfig = System.IO.File.ReadAllLines(pathConfig);
            int nouvelleTaille = 12 + listBoxZones.Items.Count;
            string[] nouveauFichierConfig = new string[nouvelleTaille];

            //copie les config dans le nouveau fichier
            for (int i = 0; i < 12; i++)
                nouveauFichierConfig[i] = fichierConfig[i];
           
            //enrregistre les partie du le comboList dans le fichier
            int j = 12;
            foreach (ComboBoxItem item in listBoxZones.Items) 
            {
                //enleve le \0 de la fin si il en a un
                string path = item.Value.Replace("\0", string.Empty);
                nouveauFichierConfig[j] = path;
                j++;
            }

            System.IO.File.WriteAllLines(pathConfig, nouveauFichierConfig);
         
        }

        private void button1_Click(object sender, EventArgs e)
        {
            listBoxZones.Items.Clear();
            recupererCampagneEnregistre();
        }

    }
}
