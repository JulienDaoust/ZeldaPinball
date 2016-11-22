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
using System.Runtime.InteropServices;
using System.Collections;

namespace InterfaceGraphique
{
    /// <summary>
    /// Cette classe représente le menu de préparation d'une partie rapide
    /// </summary>
    public partial class ConfigurerPartieRapide : Form
    {
        ConfigurationPartie config;
        ZoneDeJeux zoneRapide;
        LoadScreen loadScreen;

        /// <summary>
        /// Redefinition d'un item de ComboBox
       /// </summary>
        public class ComboBoxItem
        {
            public string Text { get; set; }
            public string Value { get; set; }
            public override string ToString() { return Text; }
        }
        /// <summary>
        /// constructeur par default
        /// </summary>
        public ConfigurerPartieRapide()
        {
            InitializeComponent();
            config = new ConfigurationPartie();
            zoneRapide = new ZoneDeJeux();
            chargerZones();
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
            if (String.Compare(nomEtExtention[1], "xml", true) == 0)
            {
                return nomEtExtention[0];
            }

            return "pasXML";
        }


        /// <summary>
        /// configure le comboBoxZones pour offir le choix des Zones disponibles dans le fichier Zones
        /// 
        /// on vas chercher tout les fichier .xml qui sont dans ...\zones\ et on les liste dans le comboBox
        /// /
        /// </summary>
        private void chargerZones()
        {
            string initPath = Application.StartupPath + @"\zones";

            //getFile retourne un tableau avec le path de tout les fichiers
            foreach (string path in Directory.GetFiles(initPath))
            {
                if (File.Exists(path))
                {

                    string localPath = path;
                    string nomFichier = getNomXML(path);

                    if (localPath != string.Empty)
                        localPath += "\0";

                    ComboBoxItem zoneValide = new ComboBoxItem();
                    zoneValide.Text = nomFichier;
                    zoneValide.Value = localPath;
                    comboBoxZones.Items.Add(zoneValide);

                    /*
                    //si le fichie a un extention xml, son nom est ajouté au comboBox
                    string nomFichier = getNomXML(path);

                    if (nomFichier != "pasXML")
                    {
                        ComboBoxItem zoneValide = new ComboBoxItem();
                        zoneValide.Text = nomFichier;
                        zoneValide.Value = path + "\0";
                        comboBoxZones.Items.Add(zoneValide);
                    }
                    else
                    
                        Console.WriteLine("{0} is not a valid file or directory.", path);
                    */
                }
            }

        }

        public void demarerPartieSimple()
        {
            this.Hide();
            //Création de la partie
            Program.partieRapide = new PartieRapide(zoneRapide, config);
            //fenetre de chargement de la partie
            loadScreen = new LoadScreen(zoneRapide);
            loadScreen.ShowDialog();
            FonctionsNatives.activerSonBackground();
            //affichage de la partie rapide
            var resultatPartie = Program.partieRapide.ShowDialog();
            FonctionsNatives.reinitialiserPartie();
            //si la partie est perdue
            if (resultatPartie == DialogResult.No)
            {
                var result = MessageBox.Show("Voulez vous rejouer cette partie? ", " Vous avez perdu! ", MessageBoxButtons.YesNo);
                if (result == DialogResult.Yes)
                {
                    demarerPartieSimple();
                }
                else
                {
                    Program.menuPrincipal.Show();
                    this.Close();
                    
                }
            }
            //Si la dernierre zone est réussi
            else if (resultatPartie == DialogResult.OK)
            {
                var result = MessageBox.Show("Voulez vous rejouer cette partie? ", " Vous avez réussi. ", MessageBoxButtons.YesNo);
                if (result == DialogResult.Yes)
                {
                    demarerPartieSimple();
                }
                else
                {
                    Program.menuPrincipal.Show();
                    this.Close();
                }
            }
            Program.menuPrincipal.Show();
            this.Close();
        }

        private void buttonDebuter_Click(object sender, EventArgs e)
        {
            demarerPartieSimple();
        }

        private void buttonAnuler_Click(object sender, EventArgs e)
        {
            this.Close();
            Program.menuPrincipal.Show();
        }

        private void ConfigurationsPartieSimple_FormClosed(object sender, FormClosedEventArgs e)
        {
            Program.menuPrincipal.Show();
            this.Dispose();
        }


        private void comboBoxZones_SelectionChangeCommitted(object sender, EventArgs e)
        {

            string path = ((ComboBoxItem)comboBoxZones.SelectedItem).Value;
            string nom = ((ComboBoxItem)comboBoxZones.SelectedItem).ToString();
            int difficulte = FonctionsNatives.obtenirDifficulte(path.ToCharArray(0, path.Length));

            //actualisation de la zone actuelle
            zoneRapide.actualiserZone(path, nom, difficulte);

            buttonDebuter.Enabled = true;

        }

        private void radioVirtuel_CheckedChanged(object sender, EventArgs e)
        {
            config.joueurVirtuel_ = true;
        }

        private void radioSinglePlayer_CheckedChanged(object sender, EventArgs e)
        {
            config.estMultiplayer_ = false;
            groupBoxDeuxiemmeJoueur.Visible = false;
            radioButtonHumain.Checked = true;

        }

        private void radioButtonCoop_CheckedChanged(object sender, EventArgs e)
        {
            config.estMultiplayer_ = true;
            groupBoxDeuxiemmeJoueur.Visible = true;
        }

        private void radioButtonHumain_CheckedChanged(object sender, EventArgs e)
        {
            config.joueurVirtuel_ = false;
        }




    }

    static partial class FonctionsNatives
    {
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int obtenirDifficulte(char[] nomFichier);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int verifierIntegriteXML(char[] nomFichier);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void affichageTexte();
    }
}
