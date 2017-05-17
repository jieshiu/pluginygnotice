using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using RTXSAPILib;
using System.Runtime.InteropServices;
using System.IO;
using System.Net;

namespace APIObject
{
    public partial class Form1 : Form
    {
        RTXSAPILib.RTXSAPIRootObj RootObj;  //����һ��������
        RTXSAPILib.RTXSAPIObj ApiObj;       //����һ��Ӧ�ö���
        RTXSAPILib.RTXSAPIMessage MsgObj;   //����һ����Ϣ����
        RTXSAPILib.RTXSData DataObj;        //����һ��SData����

        public delegate void AddText(RTXSAPILib.RTXSAPIMessage strMessage);
        public AddText mydelegate;
        HttpWebResponse Response = null;
        public Form1()
        {
            InitializeComponent();

            RootObj = new RTXSAPIRootObj();     //����������
            ApiObj = RootObj.CreateAPIObj();    //ͨ�������󴴽�Ӧ�ö���
            MsgObj = ApiObj.CreateMessage();    //ͨ��Ӧ�ö��󴴽���Ϣ����
            DataObj = RootObj.CreateRTXSData(); //ͨ�������󴴽�SData����

            ApiObj.OnRecvMessage +=new _IRTXSAPIObjEvents_OnRecvMessageEventHandler(ApiObj_OnRecvMessage); //����һ���¼������յ��ͻ��˲������������Ϣʱ�������¼�

            mydelegate = new AddText(AddTextMethod);
        }

        public void AddTextMethod(RTXSAPILib.RTXSAPIMessage strMessage)
        {
            txtResult.Text = strMessage.Sender + "����:" + strMessage.Content + "��:" + strMessage.Receivers;
            txtReceiver.Text = strMessage.Sender;

        }
        
        private void SendNoticeData(string csSendData, string csReceiver)
        {

            RTXSAPILib.RTXSData sendData = RootObj.CreateRTXSData(); // ����һ��SData����

            //��װЭ����������SDataObj��һ��Э�������Э�������װ����Ϣ����MsgObj��Ȼ�����Ӧ�ö����SendMessage������MsgObj���͸��ͻ���
            sendData.SetString("Sender", "{16F8F6DB-EB21-4520-8371-421DD76A9149}");  // ���÷�����
            sendData.SetString("Content", csSendData);   // ������Ϣ����
            //Ϊ��������⣬��ʾ��Э���ֻ�������ֶΣ���Щ�ֶ����ƿ����������ơ�

            MsgObj.Sender = "{16F8F6DB-EB21-4520-8371-421DD76A9149}";//'���÷����ߣ���GUIDΪӦ�õ�GUID��
            MsgObj.Receivers = csReceiver;  //���ý�����
            MsgObj.MsgType = "Tencent.RTX.PlugInYgNotice"; //������Ϣ���ͣ�����Ϣ���Ϳ����ڿͻ��˲���鿴
            MsgObj.AppName = "Tencent.RTX.PlugInYgNotice";  //����Ϊ�ͻ��˲�������ƣ��������һ������Ϣ����һ��
            MsgObj.Content = sendData.XML; // ��SData����Ϊxml��ʽ��ֵ��Content
            MsgObj.MessageFlag = RTXSAPI_MESSAGE_FLAG.RTXSAPI_MESSAGE_FLAG_DEFAULT; //Ĭ�ϵĴ���ʽ����������Ӧ�ù�����Ϣ��Ҳ�����Գ�ȡ�ķ�ʽ����Ϣ���й���

            try
            {
                ApiObj.SendMessage(MsgObj, false); //��MsgObj�����ͻ���

            }
            catch (COMException xe)
            {
                //MessageBox.Show(xe.Message);
            }

        }

        private void ApiObj_OnRecvMessage(RTXSAPILib.RTXSAPIMessage Message) //���յ������������Ϣ�������¼�
        {
            try
            {
                txtResult.BeginInvoke(mydelegate, Message); //����Ϣ��ʾ���ı���


                //��Э�������Message.Content��ֵ��һ��SData����ͨ��SData����ķ�����ȡ�����ֶε�ֵ
                RTXSAPILib.RTXSData ReceiverData; //����һ��SData����     
                ReceiverData = RootObj.CreateRTXSData();  //������
                ReceiverData.XML = Message.Content;// ��Message.Content��ֵ��ReceiverData.XML
                string csSend=ReceiverData.GetString("Sender");
                string csReceiver = ReceiverData.GetString("Receiver");
                string csSendTime = ReceiverData.GetString("SendTime");
                string csType = ReceiverData.GetString("Type");
                string csContent = ReceiverData.GetString("Content");

                if (csType == "NOTICE")
                {
                    string csSendNotice = "NOTICE|" + csReceiver + "|0|" + csContent;
                    SendNoticeData(csSendNotice, csReceiver);
                }
                else if(csType == "TALK")
                {                    
                    //string returnMess = ConnectTuLing(csContent); 
                    string returnMess = "�����ڴ���";
                    string csSendTalk = "TALK|" + returnMess;
                    SendNoticeData(csSendTalk, csSend);
                }


            }
            catch (COMException xe)
            {
                MessageBox.Show(xe.Message);
            }

        }

        private void btnRegApp_Click(object sender, EventArgs e)
        {
            ApiObj.ServerIP = txtServerIP.Text;    //���÷�����IP,,�������
            ApiObj.ServerPort = Convert.ToInt16(txtServerPort.Text);    //���÷������˿�,,�������
            ApiObj.AppGUID = txtAppGuid.Text;      //����Ӧ��GUID,,�������
            ApiObj.AppName = txtAppName.Text;      //����Ӧ������,,�������


            if (txtFilterAction.Text == "distill")  
            {
                ApiObj.AppAction = RTXSAPI_APP_ACTION.AA_DISTILL;
            }
            else if (txtFilterAction.Text == "copy")        // �����˶���ΪAA_DISTILLʱ��ConServer����Ϣ������Ӧ�ú�ɾ��ԭ������Ϣ��
            {
                ApiObj.AppAction = RTXSAPI_APP_ACTION.AA_COPY; //���ù��˶���,�����˶���ΪAA_COPYʱ��ConServer����Ϣ����һ�ݸ�Ӧ�ã�������ɾ��ԭ������Ϣ��
            }
            else
            {
                MessageBox.Show("������������������");

            }



            ApiObj.FilterAppName = "All";   // ��ʾ��������Ӧ��,�������
            ApiObj.FilterRequestType = txtFilterRequestTy.Text ; // ������Ϣ����,�������
            ApiObj.FilterResponseType = "none"; // �޻ظ���Ϣ����,�������
            ApiObj.FilterSender = "anyone";    //�������з����˵ĸ�����Ϣ,�������
            ApiObj.FilterReceiver = "anyone"; //�������н����˵ĸ�����Ϣ,�������
            ApiObj.FilterReceiverState = "anystate" ; // ��ע����״̬,�������
            ApiObj.FilterKey = "";


            try
            {
                ApiObj.RegisterApp();   //ע��Ӧ��
                MessageBox.Show("ע��ɹ�");

            }
            catch (COMException xe)
            {
                MessageBox.Show(xe.Message);
            }

        }



        private void btnStartApp_Click(object sender, EventArgs e)
        {
            try
            {
                ApiObj.StartApp("", 4);     //����Ӧ��
                MessageBox.Show("�����ɹ�");
            }
            catch (COMException xe)
            {
                MessageBox.Show(xe.Message);
            }

        }

        private void btnStopApp_Click(object sender, EventArgs e)
        {
            try
            {
                ApiObj.StopApp();   //ֹͣӦ��
                MessageBox.Show("ֹͣ�ɹ�");
            }
            catch (COMException xe)
            {
                MessageBox.Show(xe.Message);
            }
        }

        private void btnUnregApp_Click(object sender, EventArgs e)
        {
            try
            {
                ApiObj.ServerIP = txtServerIP.Text;    //���÷�����IP,,�������
                ApiObj.ServerPort = Convert.ToInt16(txtServerPort.Text);    //���÷������˿�,,�������
                ApiObj.AppGUID = txtAppGuid.Text;      //����Ӧ��GUID,,�������
                ApiObj.AppName = txtAppName.Text;      //����Ӧ������,,�������
                ApiObj.UnRegisterApp();     //ע��Ӧ��
                MessageBox.Show("ע���ɹ�");
            }
            catch (COMException xe)
            {
                MessageBox.Show(xe.Message);
            }
        }

        private void btnSendData_Click(object sender, EventArgs e)
        {

            RTXSAPILib.RTXSData sendData  = RootObj .CreateRTXSData (); // ����һ��SData����

            //��װЭ����������SDataObj��һ��Э�������Э�������װ����Ϣ����MsgObj��Ȼ�����Ӧ�ö����SendMessage������MsgObj���͸��ͻ���
            sendData.SetString ("Sender", "{16F8F6DB-EB21-4520-8371-421DD76A9149}");  // ���÷�����
            sendData.SetString ("Content", txtContent .Text );   // ������Ϣ����
            //Ϊ��������⣬��ʾ��Э���ֻ�������ֶΣ���Щ�ֶ����ƿ����������ơ�

            MsgObj.Sender = "{16F8F6DB-EB21-4520-8371-421DD76A9149}";//'���÷����ߣ���GUIDΪӦ�õ�GUID��
            MsgObj.Receivers = txtReceiver.Text;  //���ý�����
            MsgObj.MsgType = "Tencent.RTX.PlugInYgNotice"; //������Ϣ���ͣ�����Ϣ���Ϳ����ڿͻ��˲���鿴
            MsgObj.AppName = "Tencent.RTX.PlugInYgNotice";  //����Ϊ�ͻ��˲�������ƣ��������һ������Ϣ����һ��
            MsgObj.Content = sendData.XML; // ��SData����Ϊxml��ʽ��ֵ��Content
            MsgObj.MessageFlag = RTXSAPI_MESSAGE_FLAG .RTXSAPI_MESSAGE_FLAG_DEFAULT ; //Ĭ�ϵĴ���ʽ����������Ӧ�ù�����Ϣ��Ҳ�����Գ�ȡ�ķ�ʽ����Ϣ���й���

            try
            {
                ApiObj .SendMessage (MsgObj,false ); //��MsgObj�����ͻ���

            }
            catch (COMException xe)
            {
                MessageBox.Show(xe.Message);
            }

        }

    }
}