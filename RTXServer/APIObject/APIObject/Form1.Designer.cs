namespace APIObject
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
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.txtServerIP = new System.Windows.Forms.TextBox();
            this.txtServerPort = new System.Windows.Forms.TextBox();
            this.txtAppGuid = new System.Windows.Forms.TextBox();
            this.txtAppName = new System.Windows.Forms.TextBox();
            this.txtFilterRequestTy = new System.Windows.Forms.TextBox();
            this.txtFilterAction = new System.Windows.Forms.TextBox();
            this.txtResult = new System.Windows.Forms.TextBox();
            this.txtContent = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.btnRegApp = new System.Windows.Forms.Button();
            this.btnStartApp = new System.Windows.Forms.Button();
            this.btnStopApp = new System.Windows.Forms.Button();
            this.btnUnregApp = new System.Windows.Forms.Button();
            this.btnSendData = new System.Windows.Forms.Button();
            this.label9 = new System.Windows.Forms.Label();
            this.txtReceiver = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // txtServerIP
            // 
            this.txtServerIP.Location = new System.Drawing.Point(110, 25);
            this.txtServerIP.Name = "txtServerIP";
            this.txtServerIP.Size = new System.Drawing.Size(171, 21);
            this.txtServerIP.TabIndex = 0;
            this.txtServerIP.Text = "127.0.0.1";
            // 
            // txtServerPort
            // 
            this.txtServerPort.Location = new System.Drawing.Point(388, 25);
            this.txtServerPort.Name = "txtServerPort";
            this.txtServerPort.Size = new System.Drawing.Size(171, 21);
            this.txtServerPort.TabIndex = 1;
            this.txtServerPort.Text = "8006";
            // 
            // txtAppGuid
            // 
            this.txtAppGuid.Location = new System.Drawing.Point(110, 63);
            this.txtAppGuid.Name = "txtAppGuid";
            this.txtAppGuid.Size = new System.Drawing.Size(171, 21);
            this.txtAppGuid.TabIndex = 2;
            this.txtAppGuid.Text = "{16F8F6DB-EB21-4520-8371-421DD76A9149}";
            // 
            // txtAppName
            // 
            this.txtAppName.Location = new System.Drawing.Point(388, 63);
            this.txtAppName.Name = "txtAppName";
            this.txtAppName.Size = new System.Drawing.Size(171, 21);
            this.txtAppName.TabIndex = 3;
            this.txtAppName.Text = "CsDemoServer";
            // 
            // txtFilterRequestTy
            // 
            this.txtFilterRequestTy.Location = new System.Drawing.Point(110, 103);
            this.txtFilterRequestTy.Name = "txtFilterRequestTy";
            this.txtFilterRequestTy.Size = new System.Drawing.Size(171, 21);
            this.txtFilterRequestTy.TabIndex = 4;
            this.txtFilterRequestTy.Text = "Tencent.RTX.PlugInYgNotice";
            // 
            // txtFilterAction
            // 
            this.txtFilterAction.Location = new System.Drawing.Point(388, 103);
            this.txtFilterAction.Name = "txtFilterAction";
            this.txtFilterAction.Size = new System.Drawing.Size(171, 21);
            this.txtFilterAction.TabIndex = 5;
            this.txtFilterAction.Text = "distill";
            // 
            // txtResult
            // 
            this.txtResult.Location = new System.Drawing.Point(29, 235);
            this.txtResult.Multiline = true;
            this.txtResult.Name = "txtResult";
            this.txtResult.Size = new System.Drawing.Size(530, 85);
            this.txtResult.TabIndex = 6;
            // 
            // txtContent
            // 
            this.txtContent.Location = new System.Drawing.Point(29, 357);
            this.txtContent.Multiline = true;
            this.txtContent.Name = "txtContent";
            this.txtContent.Size = new System.Drawing.Size(530, 85);
            this.txtContent.TabIndex = 7;
            this.txtContent.Text = "服务器应用发给插件的数据";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(27, 28);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(77, 12);
            this.label1.TabIndex = 8;
            this.label1.Text = "服务器地址：";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(39, 66);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(65, 12);
            this.label2.TabIndex = 9;
            this.label2.Text = "应用标示：";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(15, 106);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(89, 12);
            this.label3.TabIndex = 10;
            this.label3.Text = "过滤消息类型：";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(305, 28);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(77, 12);
            this.label4.TabIndex = 11;
            this.label4.Text = "服务器端口：";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(317, 66);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(65, 12);
            this.label5.TabIndex = 12;
            this.label5.Text = "应用名称：";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(317, 106);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(65, 12);
            this.label6.TabIndex = 13;
            this.label6.Text = "过滤动作：";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(27, 211);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(137, 12);
            this.label7.TabIndex = 14;
            this.label7.Text = "接收插件发过来的数据：";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(27, 342);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(101, 12);
            this.label8.TabIndex = 15;
            this.label8.Text = "发送数据给插件：";
            // 
            // btnRegApp
            // 
            this.btnRegApp.Location = new System.Drawing.Point(33, 162);
            this.btnRegApp.Name = "btnRegApp";
            this.btnRegApp.Size = new System.Drawing.Size(96, 27);
            this.btnRegApp.TabIndex = 16;
            this.btnRegApp.Text = "注册应用";
            this.btnRegApp.UseVisualStyleBackColor = true;
            this.btnRegApp.Click += new System.EventHandler(this.btnRegApp_Click);
            // 
            // btnStartApp
            // 
            this.btnStartApp.Location = new System.Drawing.Point(174, 162);
            this.btnStartApp.Name = "btnStartApp";
            this.btnStartApp.Size = new System.Drawing.Size(96, 27);
            this.btnStartApp.TabIndex = 17;
            this.btnStartApp.Text = "启动应用";
            this.btnStartApp.UseVisualStyleBackColor = true;
            this.btnStartApp.Click += new System.EventHandler(this.btnStartApp_Click);
            // 
            // btnStopApp
            // 
            this.btnStopApp.Location = new System.Drawing.Point(315, 162);
            this.btnStopApp.Name = "btnStopApp";
            this.btnStopApp.Size = new System.Drawing.Size(96, 27);
            this.btnStopApp.TabIndex = 18;
            this.btnStopApp.Text = "停止应用";
            this.btnStopApp.UseVisualStyleBackColor = true;
            this.btnStopApp.Click += new System.EventHandler(this.btnStopApp_Click);
            // 
            // btnUnregApp
            // 
            this.btnUnregApp.Location = new System.Drawing.Point(456, 162);
            this.btnUnregApp.Name = "btnUnregApp";
            this.btnUnregApp.Size = new System.Drawing.Size(96, 27);
            this.btnUnregApp.TabIndex = 19;
            this.btnUnregApp.Text = "注销应用";
            this.btnUnregApp.UseVisualStyleBackColor = true;
            this.btnUnregApp.Click += new System.EventHandler(this.btnUnregApp_Click);
            // 
            // btnSendData
            // 
            this.btnSendData.Location = new System.Drawing.Point(255, 457);
            this.btnSendData.Name = "btnSendData";
            this.btnSendData.Size = new System.Drawing.Size(96, 27);
            this.btnSendData.TabIndex = 20;
            this.btnSendData.Text = "发送";
            this.btnSendData.UseVisualStyleBackColor = true;
            this.btnSendData.Click += new System.EventHandler(this.btnSendData_Click);
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(27, 464);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(53, 12);
            this.label9.TabIndex = 21;
            this.label9.Text = "接收者：";
            // 
            // txtReceiver
            // 
            this.txtReceiver.Location = new System.Drawing.Point(86, 461);
            this.txtReceiver.Name = "txtReceiver";
            this.txtReceiver.Size = new System.Drawing.Size(111, 21);
            this.txtReceiver.TabIndex = 4;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(613, 496);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.btnSendData);
            this.Controls.Add(this.btnUnregApp);
            this.Controls.Add(this.btnStopApp);
            this.Controls.Add(this.btnStartApp);
            this.Controls.Add(this.btnRegApp);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.txtContent);
            this.Controls.Add(this.txtResult);
            this.Controls.Add(this.txtFilterAction);
            this.Controls.Add(this.txtReceiver);
            this.Controls.Add(this.txtFilterRequestTy);
            this.Controls.Add(this.txtAppName);
            this.Controls.Add(this.txtAppGuid);
            this.Controls.Add(this.txtServerPort);
            this.Controls.Add(this.txtServerIP);
            this.Name = "Form1";
            this.Text = "CsDemoServer";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox txtServerIP;
        private System.Windows.Forms.TextBox txtServerPort;
        private System.Windows.Forms.TextBox txtAppGuid;
        private System.Windows.Forms.TextBox txtAppName;
        private System.Windows.Forms.TextBox txtFilterRequestTy;
        private System.Windows.Forms.TextBox txtFilterAction;
        private System.Windows.Forms.TextBox txtResult;
        private System.Windows.Forms.TextBox txtContent;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Button btnRegApp;
        private System.Windows.Forms.Button btnStartApp;
        private System.Windows.Forms.Button btnStopApp;
        private System.Windows.Forms.Button btnUnregApp;
        private System.Windows.Forms.Button btnSendData;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.TextBox txtReceiver;
    }
}

