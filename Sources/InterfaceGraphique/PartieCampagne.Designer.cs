namespace InterfaceGraphique
{
    partial class PartieCampagne
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
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fichierToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuPrincipalToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.vuesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.orthographiqueToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.orbiteToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.panel1 = new System.Windows.Forms.Panel();
            this.dEBUGToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.nextZoneToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fichierToolStripMenuItem,
            this.vuesToolStripMenuItem,
            this.dEBUGToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(1318, 53);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fichierToolStripMenuItem
            // 
            this.fichierToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuPrincipalToolStripMenuItem});
            this.fichierToolStripMenuItem.Name = "fichierToolStripMenuItem";
            this.fichierToolStripMenuItem.Size = new System.Drawing.Size(125, 49);
            this.fichierToolStripMenuItem.Text = "Fichier";
            // 
            // menuPrincipalToolStripMenuItem
            // 
            this.menuPrincipalToolStripMenuItem.Name = "menuPrincipalToolStripMenuItem";
            this.menuPrincipalToolStripMenuItem.Size = new System.Drawing.Size(437, 50);
            this.menuPrincipalToolStripMenuItem.Text = "Menu Principal (Ctrl+Q)";
            this.menuPrincipalToolStripMenuItem.Click += new System.EventHandler(this.menuPrincipalToolStripMenuItem_Click);
            // 
            // vuesToolStripMenuItem
            // 
            this.vuesToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.orthographiqueToolStripMenuItem,
            this.orbiteToolStripMenuItem});
            this.vuesToolStripMenuItem.Name = "vuesToolStripMenuItem";
            this.vuesToolStripMenuItem.Size = new System.Drawing.Size(101, 49);
            this.vuesToolStripMenuItem.Text = "Vues";
            // 
            // orthographiqueToolStripMenuItem
            // 
            this.orthographiqueToolStripMenuItem.Name = "orthographiqueToolStripMenuItem";
            this.orthographiqueToolStripMenuItem.Size = new System.Drawing.Size(328, 50);
            this.orthographiqueToolStripMenuItem.Text = "Orthographique";
            // 
            // orbiteToolStripMenuItem
            // 
            this.orbiteToolStripMenuItem.Name = "orbiteToolStripMenuItem";
            this.orbiteToolStripMenuItem.Size = new System.Drawing.Size(328, 50);
            this.orbiteToolStripMenuItem.Text = "Orbite";
            // 
            // panel1
            // 
            this.panel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel1.Location = new System.Drawing.Point(0, 53);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(1318, 845);
            this.panel1.TabIndex = 1;
            // 
            // dEBUGToolStripMenuItem
            // 
            this.dEBUGToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.nextZoneToolStripMenuItem});
            this.dEBUGToolStripMenuItem.Name = "dEBUGToolStripMenuItem";
            this.dEBUGToolStripMenuItem.Size = new System.Drawing.Size(150, 49);
            this.dEBUGToolStripMenuItem.Text = "!DEBUG!";
            // 
            // nextZoneToolStripMenuItem
            // 
            this.nextZoneToolStripMenuItem.Name = "nextZoneToolStripMenuItem";
            this.nextZoneToolStripMenuItem.Size = new System.Drawing.Size(248, 50);
            this.nextZoneToolStripMenuItem.Text = "Next Zone";
            this.nextZoneToolStripMenuItem.Click += new System.EventHandler(this.nextZoneToolStripMenuItem_Click);
            // 
            // PartieCampagne
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(12F, 25F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1318, 898);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Margin = new System.Windows.Forms.Padding(6);
            this.Name = "PartieCampagne";
            this.Text = "PartieCampagne";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.PartieCampagne_FormClosed);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

       

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.ToolStripMenuItem fichierToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem menuPrincipalToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem vuesToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem orthographiqueToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem orbiteToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem dEBUGToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem nextZoneToolStripMenuItem;
    }
}