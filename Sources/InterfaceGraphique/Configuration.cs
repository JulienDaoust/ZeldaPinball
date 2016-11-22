using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.IO;

namespace InterfaceGraphique
{
    /// <summary>
    /// Classe qui gere les configurations du jeu
    /// </summary>
    public partial class Configuration : Form
    {
        /// <summary>
        /// Petite fenetre qui apparait lorsquon clique dans un textbox
        /// </summary>
        KeyPress toucheMenu;

        /// <summary>
        /// Touches configurée à l'ouverture de l'application
        /// </summary>
        Keys[] currentKeys = new Keys[5];

        /// <summary>
        /// String lues dans le fichier Config.txt
        /// </summary>
        String Touche1, Touche2, Touche3, Touche4, Touche5, NbBille, DoubleBille, Debug, Debug1, Debug2, Debug3, Debug4;

        /// <summary>
        /// Variables qui vérifie quelle configurations ont été modifié dans la fenêtre
        /// </summary>
        bool paletteDJ1 = false;
        bool paletteGJ1 = false;
        bool paletteDJ2 = false;
        bool paletteGJ2 = false;
        bool ressort = false;
        bool position = false;
        bool vitesse = false;
        bool eclairage = false;
        bool attraction = false;

        /// <summary>
        /// Constructeur de la classe Configuration
        /// </summary>
        public Configuration()
        {
            InitializeComponent();
            try
            {
                string path = Application.StartupPath + "/données/Config.txt";
                using (StreamReader sr = new StreamReader(path))
                {
                    Touche1 = sr.ReadLine();
                    Touche2 = sr.ReadLine();
                    Touche3 = sr.ReadLine();
                    Touche4 = sr.ReadLine();
                    Touche5 = sr.ReadLine();
                    NbBille = sr.ReadLine();
                    DoubleBille = sr.ReadLine();
                    Debug = sr.ReadLine();
                    Debug1 = sr.ReadLine();
                    Debug2 = sr.ReadLine();
                    Debug3 = sr.ReadLine();
                    Debug4 = sr.ReadLine();
                }

            }
            catch (Exception e)
            {
                Console.WriteLine("Le fichier de configuration n'a pu etre ouvert");
                Console.WriteLine(e.Message);
            }

            comboBox1.Text = NbBille;
            comboBox2.Text = DoubleBille;
            comboBox3.Text = Debug;
            comboBox4.Text = Debug1;
            comboBox5.Text = Debug2;
            comboBox6.Text = Debug3;
            comboBox7.Text = Debug4;

            currentKeys[0] = (Keys) Enum.Parse(typeof(Keys), Touche1);
            currentKeys[1] = (Keys)Enum.Parse(typeof(Keys), Touche2);
            currentKeys[2] = (Keys)Enum.Parse(typeof(Keys), Touche3);
            currentKeys[3] = (Keys)Enum.Parse(typeof(Keys), Touche4);
            currentKeys[4] = (Keys)Enum.Parse(typeof(Keys), Touche5);

            textBox1.Text = currentKeys[0].ToString();
            textBox2.Text = currentKeys[1].ToString();
            textBox4.Text = currentKeys[2].ToString();
            textBox3.Text = currentKeys[3].ToString();
            textBox6.Text = currentKeys[4].ToString();
        }

        /// <summary>
        /// Lorsqu'on clique sur Appliquer, l'on sauvegarde les changements dans le ficheir Config.txt
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button2_Click(object sender, EventArgs e)
        {
            string path = Application.StartupPath + "/données/Config.txt";
            string[] touche = System.IO.File.ReadAllLines(path);
            touche[0] = currentKeys[0].ToString();
            touche[1] = currentKeys[1].ToString();
            touche[2] = currentKeys[2].ToString();
            touche[3] = currentKeys[3].ToString();
            touche[4] = currentKeys[4].ToString();
            touche[5] = comboBox1.Text;
            touche[6] = comboBox2.Text;
            touche[7] = comboBox3.Text;
            touche[8] = comboBox4.Text;
            touche[9] = comboBox5.Text;
            touche[10] = comboBox6.Text;
            touche[11] = comboBox7.Text;
            System.IO.File.WriteAllLines(path, touche);
            this.Hide();
            Program.menuPrincipal.Show();
        }

        /// <summary>
        /// Fonction associer au clique du bouton Annuler, celle-ci reinitialise les textbox et les touches à celle du fichier Config.txt
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button3_Click(object sender, EventArgs e)
        {
            string path = Application.StartupPath + "/données/Config.txt";
            using (StreamReader sr = new StreamReader(path))
            {
                Touche1 = sr.ReadLine();
                Touche2 = sr.ReadLine();
                Touche3 = sr.ReadLine();
                Touche4 = sr.ReadLine();
                Touche5 = sr.ReadLine();
                NbBille = sr.ReadLine();
                DoubleBille = sr.ReadLine();
                Debug = sr.ReadLine();
                Debug1 = sr.ReadLine();
                Debug2 = sr.ReadLine();
                Debug3 = sr.ReadLine();
                Debug4 = sr.ReadLine();
            }

            comboBox1.Text = NbBille;
            comboBox2.Text = DoubleBille;
            comboBox3.Text = Debug;
            comboBox4.Text = Debug1;
            comboBox5.Text = Debug2;
            comboBox6.Text = Debug3;
            comboBox7.Text = Debug4;

            currentKeys[0] = (Keys)Enum.Parse(typeof(Keys), Touche1);
            currentKeys[1] = (Keys)Enum.Parse(typeof(Keys), Touche2);
            currentKeys[2] = (Keys)Enum.Parse(typeof(Keys), Touche3);
            currentKeys[3] = (Keys)Enum.Parse(typeof(Keys), Touche4);
            currentKeys[4] = (Keys)Enum.Parse(typeof(Keys), Touche5);

            textBox1.Text = currentKeys[0].ToString();
            textBox2.Text = currentKeys[1].ToString();
            textBox4.Text = currentKeys[2].ToString();
            textBox3.Text = currentKeys[3].ToString();
            textBox6.Text = currentKeys[4].ToString();
            this.Hide();
            Program.menuPrincipal.Show();
        }

        /// <summary>
        /// Fonction associer au clique la premiere texte box. On fait apparaitre une fenetre qui enregistre la prochaine touche enfoncé
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void textBox1_MouseDown(object sender, MouseEventArgs e)
        {
            toucheMenu = new KeyPress(this);
            paletteDJ1 = true;
            toucheMenu.Show();
        }

        /// <summary>
        /// Voir textBox1_MouseDown
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void textBox2_MouseDown(object sender, MouseEventArgs e)
        {
            toucheMenu = new KeyPress(this);
            paletteGJ1 = true;
            toucheMenu.Show();
        }

        /// <summary>
        /// Voir textBox1_MouseDown
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void textBox4_MouseDown(object sender, MouseEventArgs e)
        {
            toucheMenu = new KeyPress(this);
            paletteDJ2 = true;
            toucheMenu.Show();
        }

        /// <summary>
        /// Voir textBox1_MouseDown
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void textBox3_MouseDown(object sender, MouseEventArgs e)
        {
            toucheMenu = new KeyPress(this);
            paletteGJ2 = true;
            toucheMenu.Show();
        }

        /// <summary>
        /// Voir textBox1_MouseDown
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void textBox6_MouseDown(object sender, MouseEventArgs e)
        {
            toucheMenu = new KeyPress(this);
            ressort = true;
            toucheMenu.Show();
        }

        /// <summary>
        /// Fonction appellée par toucheMenu qui vérifie la validité de la touche reçu avant de l'assigner
        /// </summary>
        /// <param name="touche"></param>
        public void toucheRecu(Keys touche)
        {
            Keys toucheEnfonce = touche;
            toucheMenu.Dispose();
            if(paletteDJ1)
            {
                if(verifierAssignation(0, touche))
                {
                    MessageBox.Show("Erreur, touche déjà assignée !");
                }
                else
                {
                    currentKeys[0] = touche;
                    textBox1.Text = touche.ToString();
                }
            }
            else if (paletteGJ1)
            {
                if (verifierAssignation(1, touche))
                {
                    MessageBox.Show("Erreur, touche déjà assignée !");
                }
                else
                {
                    currentKeys[1] = touche;
                    textBox2.Text = touche.ToString();
                }
            }
            else if (paletteDJ2)
            {
                if (verifierAssignation(2, touche))
                {
                    MessageBox.Show("Erreur, touche déjà assignée !");
                }
                else
                {
                    currentKeys[2] = touche;
                    textBox4.Text = touche.ToString();
                }
            }
            else if (paletteGJ2)
            {
                if (verifierAssignation(3, touche))
                {
                    MessageBox.Show("Erreur, touche déjà assignée !");
                }
                else
                {
                    currentKeys[3] = touche;
                    textBox3.Text = touche.ToString();
                }
            }
            else if (ressort)
            {
                if (verifierAssignation(4 , touche))
                {
                    MessageBox.Show("Erreur, touche déjà assignée !");
                }
                else
                {
                    currentKeys[4] = touche;
                    textBox6.Text = touche.ToString();
                }
            }
            paletteDJ1 = false;
            paletteGJ1 = false;
            paletteDJ2 = false;
            paletteGJ2 = false;
            ressort = false;
        }

        /// <summary>
        /// Bouton default, on refait les valeurs des touches à celle predefinie
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button1_Click(object sender, EventArgs e)
        {
            currentKeys[0] = Keys.A;
            currentKeys[1] = Keys.S;
            currentKeys[2] = Keys.D4;
            currentKeys[3] = Keys.D5;
            currentKeys[4] = Keys.Space;
            textBox1.Text = currentKeys[0].ToString();
            textBox2.Text = currentKeys[1].ToString();
            textBox4.Text = currentKeys[2].ToString();
            textBox3.Text = currentKeys[3].ToString();
            textBox6.Text = currentKeys[4].ToString();

        }

        /// <summary>
        /// On verifier si les touches sont deja assigneé
        /// </summary>
        /// <param name="typePalette">Le type de touche que l'on verifie</param>
        /// <param name="touche">La touche que l'on veut verifier</param>
        /// <returns>Vrai si la touche est deja assignée, faux sinon</returns>
        public bool verifierAssignation(int typePalette, Keys touche)
        {
            for (int i = 0; i < 5; i++)
            {
                if (currentKeys[i] == touche && typePalette != i)
                    return true;
            }
            if (touche == Keys.Back || touche == Keys.Escape || touche == Keys.J || touche == Keys.K || touche == Keys.L || touche == Keys.T)
                return true;
            return false;
        }

        /// <summary>
        /// Desactive les 5 textbox pour ne plus qu'elles soient cliquables
        /// </summary>
        public void desactiverEntre()
        {
            textBox1.Enabled = false;
            textBox2.Enabled = false;
            textBox3.Enabled = false;
            textBox4.Enabled = false;
            textBox6.Enabled = false;
        }

        /// <summary>
        /// Active les 5 textbox pour qu'elles redeviennent cliquables
        /// </summary>
        public void activerEntre()
        {
            textBox1.Enabled = true;
            textBox2.Enabled = true;
            textBox3.Enabled = true;
            textBox4.Enabled = true;
            textBox6.Enabled = true;
        }

        /// <summary>
        /// Active ou desactive le debug des nouvelles billes
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void comboBox4_TabIndexChanged(object sender, EventArgs e)
        {
            position = !position;
        }

        /// <summary>
        /// Active ou desactive le debug des vitesse post-collision
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void comboBox5_SelectedIndexChanged(object sender, EventArgs e)
        {
            vitesse = !vitesse;
        }

        /// <summary>
        /// Active ou desactive le debug du type d'eclairage
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void comboBox6_SelectedIndexChanged(object sender, EventArgs e)
        {
            eclairage = !eclairage;
        }

        /// <summary>
        /// Active ou desactive le debug qui affiche l'attraction des portails
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void comboBox7_SelectedIndexChanged(object sender, EventArgs e)
        {
            attraction = !attraction;
        }

        /// <summary>
        /// On cache la fenêtre, on affiche le menu principal
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Configuration_FormClosed(object sender, FormClosedEventArgs e)
        {
            Program.menuPrincipal.Show();
            this.Hide();
        }

        
    }
}
