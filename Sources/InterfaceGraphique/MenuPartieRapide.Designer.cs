namespace InterfaceGraphique
{
    partial class ConfigurerPartieRapide
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.radioSinglePlayer = new System.Windows.Forms.RadioButton();
            this.radioButtonCoop = new System.Windows.Forms.RadioButton();
            this.groupChoixTypePartie = new System.Windows.Forms.GroupBox();
            this.groupBoxDeuxiemmeJoueur = new System.Windows.Forms.GroupBox();
            this.radioButtonHumain = new System.Windows.Forms.RadioButton();
            this.radioVirtuel = new System.Windows.Forms.RadioButton();
            this.buttonAnuler = new System.Windows.Forms.Button();
            this.buttonDebuter = new System.Windows.Forms.Button();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.groupBoxChoixZone = new System.Windows.Forms.GroupBox();
            this.comboBoxZones = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.directoryEntry1 = new System.DirectoryServices.DirectoryEntry();
            this.groupChoixTypePartie.SuspendLayout();
            this.groupBoxDeuxiemmeJoueur.SuspendLayout();
            this.groupBoxChoixZone.SuspendLayout();
            this.SuspendLayout();
            // 
            // radioSinglePlayer
            // 
            this.radioSinglePlayer.AutoSize = true;
            this.radioSinglePlayer.Checked = true;
            this.radioSinglePlayer.Location = new System.Drawing.Point(20, 31);
            this.radioSinglePlayer.Margin = new System.Windows.Forms.Padding(4);
            this.radioSinglePlayer.Name = "radioSinglePlayer";
            this.radioSinglePlayer.Size = new System.Drawing.Size(86, 29);
            this.radioSinglePlayer.TabIndex = 0;
            this.radioSinglePlayer.TabStop = true;
            this.radioSinglePlayer.Text = "Solo";
            this.radioSinglePlayer.UseVisualStyleBackColor = true;
            this.radioSinglePlayer.CheckedChanged += new System.EventHandler(this.radioSinglePlayer_CheckedChanged);
            // 
            // radioButtonCoop
            // 
            this.radioButtonCoop.AutoSize = true;
            this.radioButtonCoop.Location = new System.Drawing.Point(20, 65);
            this.radioButtonCoop.Margin = new System.Windows.Forms.Padding(4);
            this.radioButtonCoop.Name = "radioButtonCoop";
            this.radioButtonCoop.Size = new System.Drawing.Size(159, 29);
            this.radioButtonCoop.TabIndex = 1;
            this.radioButtonCoop.Text = "Coopérative";
            this.radioButtonCoop.UseVisualStyleBackColor = true;
            this.radioButtonCoop.CheckedChanged += new System.EventHandler(this.radioButtonCoop_CheckedChanged);
            // 
            // groupChoixTypePartie
            // 
            this.groupChoixTypePartie.Controls.Add(this.radioSinglePlayer);
            this.groupChoixTypePartie.Controls.Add(this.radioButtonCoop);
            this.groupChoixTypePartie.Location = new System.Drawing.Point(50, 46);
            this.groupChoixTypePartie.Margin = new System.Windows.Forms.Padding(4);
            this.groupChoixTypePartie.Name = "groupChoixTypePartie";
            this.groupChoixTypePartie.Padding = new System.Windows.Forms.Padding(4);
            this.groupChoixTypePartie.Size = new System.Drawing.Size(251, 119);
            this.groupChoixTypePartie.TabIndex = 2;
            this.groupChoixTypePartie.TabStop = false;
            this.groupChoixTypePartie.Text = "Type de partieRapide";
            // 
            // groupBoxDeuxiemmeJoueur
            // 
            this.groupBoxDeuxiemmeJoueur.Controls.Add(this.radioButtonHumain);
            this.groupBoxDeuxiemmeJoueur.Controls.Add(this.radioVirtuel);
            this.groupBoxDeuxiemmeJoueur.Location = new System.Drawing.Point(317, 46);
            this.groupBoxDeuxiemmeJoueur.Margin = new System.Windows.Forms.Padding(4);
            this.groupBoxDeuxiemmeJoueur.Name = "groupBoxDeuxiemmeJoueur";
            this.groupBoxDeuxiemmeJoueur.Padding = new System.Windows.Forms.Padding(4);
            this.groupBoxDeuxiemmeJoueur.Size = new System.Drawing.Size(218, 119);
            this.groupBoxDeuxiemmeJoueur.TabIndex = 2;
            this.groupBoxDeuxiemmeJoueur.TabStop = false;
            this.groupBoxDeuxiemmeJoueur.Text = "Deuxièmme joueur";
            this.groupBoxDeuxiemmeJoueur.Visible = false;
            // 
            // radioButtonHumain
            // 
            this.radioButtonHumain.AutoSize = true;
            this.radioButtonHumain.Checked = true;
            this.radioButtonHumain.Location = new System.Drawing.Point(20, 35);
            this.radioButtonHumain.Margin = new System.Windows.Forms.Padding(4);
            this.radioButtonHumain.Name = "radioButtonHumain";
            this.radioButtonHumain.Size = new System.Drawing.Size(116, 29);
            this.radioButtonHumain.TabIndex = 0;
            this.radioButtonHumain.TabStop = true;
            this.radioButtonHumain.Text = "Humain";
            this.radioButtonHumain.UseVisualStyleBackColor = true;
            this.radioButtonHumain.CheckedChanged += new System.EventHandler(this.radioButtonHumain_CheckedChanged);
            // 
            // radioVirtuel
            // 
            this.radioVirtuel.AutoSize = true;
            this.radioVirtuel.Location = new System.Drawing.Point(24, 73);
            this.radioVirtuel.Margin = new System.Windows.Forms.Padding(4);
            this.radioVirtuel.Name = "radioVirtuel";
            this.radioVirtuel.Size = new System.Drawing.Size(104, 29);
            this.radioVirtuel.TabIndex = 1;
            this.radioVirtuel.Text = "Virtuel";
            this.radioVirtuel.UseVisualStyleBackColor = true;
            this.radioVirtuel.CheckedChanged += new System.EventHandler(this.radioVirtuel_CheckedChanged);
            // 
            // buttonAnuler
            // 
            this.buttonAnuler.Location = new System.Drawing.Point(86, 319);
            this.buttonAnuler.Margin = new System.Windows.Forms.Padding(4);
            this.buttonAnuler.Name = "buttonAnuler";
            this.buttonAnuler.Size = new System.Drawing.Size(140, 48);
            this.buttonAnuler.TabIndex = 3;
            this.buttonAnuler.Text = "Annuler";
            this.buttonAnuler.UseVisualStyleBackColor = true;
            this.buttonAnuler.Click += new System.EventHandler(this.buttonAnuler_Click);
            // 
            // buttonDebuter
            // 
            this.buttonDebuter.Enabled = false;
            this.buttonDebuter.Location = new System.Drawing.Point(290, 319);
            this.buttonDebuter.Margin = new System.Windows.Forms.Padding(4);
            this.buttonDebuter.Name = "buttonDebuter";
            this.buttonDebuter.Size = new System.Drawing.Size(140, 48);
            this.buttonDebuter.TabIndex = 3;
            this.buttonDebuter.Text = "Démarer";
            this.buttonDebuter.UseVisualStyleBackColor = true;
            this.buttonDebuter.Click += new System.EventHandler(this.buttonDebuter_Click);
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.FileName = "openFileDialog1";
            // 
            // groupBoxChoixZone
            // 
            this.groupBoxChoixZone.Controls.Add(this.comboBoxZones);
            this.groupBoxChoixZone.Controls.Add(this.label1);
            this.groupBoxChoixZone.Location = new System.Drawing.Point(56, 177);
            this.groupBoxChoixZone.Margin = new System.Windows.Forms.Padding(4);
            this.groupBoxChoixZone.Name = "groupBoxChoixZone";
            this.groupBoxChoixZone.Padding = new System.Windows.Forms.Padding(4);
            this.groupBoxChoixZone.Size = new System.Drawing.Size(479, 135);
            this.groupBoxChoixZone.TabIndex = 6;
            this.groupBoxChoixZone.TabStop = false;
            this.groupBoxChoixZone.Text = "Choisir une zone de jeux";
            // 
            // comboBoxZones
            // 
            this.comboBoxZones.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxZones.Location = new System.Drawing.Point(209, 55);
            this.comboBoxZones.Margin = new System.Windows.Forms.Padding(4);
            this.comboBoxZones.Name = "comboBoxZones";
            this.comboBoxZones.Size = new System.Drawing.Size(200, 33);
            this.comboBoxZones.TabIndex = 8;
            this.comboBoxZones.SelectionChangeCommitted += new System.EventHandler(this.comboBoxZones_SelectionChangeCommitted);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(8, 58);
            this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(193, 25);
            this.label1.TabIndex = 6;
            this.label1.Text = "Zones disponibles:";
            // 
            // ConfigurerPartieRapide
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(12F, 25F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(606, 453);
            this.Controls.Add(this.groupBoxChoixZone);
            this.Controls.Add(this.buttonDebuter);
            this.Controls.Add(this.buttonAnuler);
            this.Controls.Add(this.groupBoxDeuxiemmeJoueur);
            this.Controls.Add(this.groupChoixTypePartie);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Margin = new System.Windows.Forms.Padding(4);
            this.Name = "ConfigurerPartieRapide";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "ConfigurerPartieSimple";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.ConfigurationsPartieSimple_FormClosed);
            this.groupChoixTypePartie.ResumeLayout(false);
            this.groupChoixTypePartie.PerformLayout();
            this.groupBoxDeuxiemmeJoueur.ResumeLayout(false);
            this.groupBoxDeuxiemmeJoueur.PerformLayout();
            this.groupBoxChoixZone.ResumeLayout(false);
            this.groupBoxChoixZone.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.RadioButton radioSinglePlayer;
        private System.Windows.Forms.RadioButton radioButtonCoop;
        private System.Windows.Forms.GroupBox groupChoixTypePartie;
        private System.Windows.Forms.GroupBox groupBoxDeuxiemmeJoueur;
        private System.Windows.Forms.RadioButton radioButtonHumain;
        private System.Windows.Forms.RadioButton radioVirtuel;
        private System.Windows.Forms.Button buttonAnuler;
        private System.Windows.Forms.Button buttonDebuter;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.GroupBox groupBoxChoixZone;
        private System.DirectoryServices.DirectoryEntry directoryEntry1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox comboBoxZones;
    }
}