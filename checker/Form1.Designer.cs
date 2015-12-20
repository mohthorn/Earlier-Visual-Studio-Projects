namespace checker
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.inputButton = new System.Windows.Forms.Button();
            this.inputText = new System.Windows.Forms.TextBox();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.menuToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.nimaseToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.debuggingToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.debuggingToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.clearToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // inputButton
            // 
            this.inputButton.Location = new System.Drawing.Point(721, 160);
            this.inputButton.Name = "inputButton";
            this.inputButton.Size = new System.Drawing.Size(106, 65);
            this.inputButton.TabIndex = 0;
            this.inputButton.Text = "确认";
            this.inputButton.UseVisualStyleBackColor = true;
            this.inputButton.Click += new System.EventHandler(this.button1_Click);
            // 
            // inputText
            // 
            this.inputText.Location = new System.Drawing.Point(689, 96);
            this.inputText.Name = "inputText";
            this.inputText.Size = new System.Drawing.Size(174, 25);
            this.inputText.TabIndex = 1;
            // 
            // menuStrip1
            // 
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuToolStripMenuItem,
            this.debuggingToolStripMenuItem,
            this.clearToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(1008, 28);
            this.menuStrip1.TabIndex = 2;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // menuToolStripMenuItem
            // 
            this.menuToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.nimaseToolStripMenuItem});
            this.menuToolStripMenuItem.Name = "menuToolStripMenuItem";
            this.menuToolStripMenuItem.Size = new System.Drawing.Size(63, 24);
            this.menuToolStripMenuItem.Text = "Menu";
            // 
            // nimaseToolStripMenuItem
            // 
            this.nimaseToolStripMenuItem.Name = "nimaseToolStripMenuItem";
            this.nimaseToolStripMenuItem.Size = new System.Drawing.Size(181, 26);
            this.nimaseToolStripMenuItem.Text = "&Nimase";
            // 
            // debuggingToolStripMenuItem
            // 
            this.debuggingToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.debuggingToolStripMenuItem1});
            this.debuggingToolStripMenuItem.Name = "debuggingToolStripMenuItem";
            this.debuggingToolStripMenuItem.Size = new System.Drawing.Size(102, 24);
            this.debuggingToolStripMenuItem.Text = "debugging";
            // 
            // debuggingToolStripMenuItem1
            // 
            this.debuggingToolStripMenuItem1.Name = "debuggingToolStripMenuItem1";
            this.debuggingToolStripMenuItem1.Size = new System.Drawing.Size(181, 26);
            this.debuggingToolStripMenuItem1.Text = "&debugging";
            // 
            // clearToolStripMenuItem
            // 
            this.clearToolStripMenuItem.Name = "clearToolStripMenuItem";
            this.clearToolStripMenuItem.Size = new System.Drawing.Size(58, 24);
            this.clearToolStripMenuItem.Text = "Clear";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1008, 526);
            this.Controls.Add(this.inputText);
            this.Controls.Add(this.inputButton);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button inputButton;
        private System.Windows.Forms.TextBox inputText;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem menuToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem nimaseToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem debuggingToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem debuggingToolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem clearToolStripMenuItem;
    }
}

