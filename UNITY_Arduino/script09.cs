using System;
using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using System.Collections.Generic;
using System.Threading ;
using System.Text.RegularExpressions;

using System.IO.Ports;
using TMPro;
/*
cet script.08 marche avec Send_data_to_unity_momo_02.ino
*/

//namespace RotConection
//{
    public class script09 : MonoBehaviour
    {
		
		private const int X_AXES       = 1;
		private const int X_AXES_ready = 2;
		private const int Y_AXES       = 3;
		private const int Y_AXES_ready = 4;
		private const int X_ACCEL_AXES = 5;
		private const int Y_ACCEL_AXES = 6;
		private const int Z_ACCEL_AXES = 7;
		private const int BUTTON1      = 8;
		private const int BUTTON2      = 9;
		private const int FIN          = 10;
		private const int ERROR        = 20;
		
        public GameObject _Cube_sensor_1;
		public GameObject _Cube_sensor_2;
		public GameObject _Cube_sensor_3;
		public GameObject _Cube_sensor_4;
		public GameObject _Cube_sensor_5;
		public GameObject _Text01;
		//public GameObject _Text02;
        public GameObject _Cube_b_sensor;
		public GameObject _Cube_sensor_12;
        public GameObject _Cube_b_sensor2;
        public GameObject _Cube_x_accel_axes;
        public GameObject _Cube_y_accel_axes;
		public GameObject _Cube_z_accel_axes;
		public GameObject button1;
		public GameObject button2;
        private TextMeshPro m_Text1,m_Text2,m_Text3,m_Text4;
        private static string message = "";
        public float Rot = 0;
        public int Vitesse = 115200;
		private static int token=0;
		private static int lasttoken=FIN;//FIN
		private	static string sensor_1_c;
		private static string b_sensor_c;
		private	static string a_sensor_c;
		private	static string d_sensor_c;
		private static string x_accel_axes_c;
		private static string y_accel_axes_c;
		private static string z_accel_axes_c;
		private static string button1_c;
		private static string button2_c;
		private static float  sensor_1_i=1;
		private static float  a_sensor_i=1;
		private static float  d_sensor_i=1;
		private static float  b_sensor_i=1;
		private static float  x_accel_axes_i=100;
		private static float  y_accel_axes_i=100;
		private static float  z_accel_axes_i=100;
		private static float  button1_i=1;
		private static float  button2_i=1;
		private static double[] sensor;
		private static double[] gps;
		
		public string NewLine { get; set; }
		//Thread readThread = new Thread(ReadSerial);

		
		
        SerialPort sp = new SerialPort("COM8", 115200);
        // Start is called before the first frame update
        void Start()
        {
            sp.ReadTimeout = 100;
            sp.WriteTimeout = 100;
			
            //m_Text1 = GetComponent<TextMeshPro>() ?? gameObject.AddComponent<TextMeshPro>();
			
            //m_Text = GameObject.Find("Text(TMP)");
            //m_Text1.text = "\0";
            Rot = 0;
            try
            {
                sp.Open();
				StartCoroutine("ReadSerial");
            }
            catch (System.Exception)
            {
                print("erreur d'ouverture du port");
            }
            message = "";
			
			sensor = new double[10];
			gps    = new double[10];
			sp.Write("y");
			
        }

        // Update is called once per frame
        void Update()
        {
			
            if (sp.IsOpen)
            {
                try
                {
                    {
						ReadSerial();
                        _Cube_sensor_1    = GameObject.Find("Cube_sensor_1");
						_Cube_sensor_2    = GameObject.Find("Cube_sensor_2");
						_Cube_sensor_3    = GameObject.Find("Cube_sensor_3");
						_Cube_sensor_4    = GameObject.Find("Cube_sensor_4");
						_Cube_sensor_5    = GameObject.Find("Cube_sensor_5");
						
						//float sensor_1_i_scale=((sensor_1_i*1f));
						if (sensor[0]==0) _Cube_sensor_1.transform.localScale = new Vector3(0.059f, 0.12f, 0.059f);
						if (sensor[0]==1) _Cube_sensor_1.transform.localScale = new Vector3(0.059f, 0.02f, 0.059f);
						if (sensor[1]==0) _Cube_sensor_2.transform.localScale = new Vector3(0.059f, 0.12f, 0.059f);
						if (sensor[1]==1) _Cube_sensor_2.transform.localScale = new Vector3(0.059f, 0.02f, 0.059f);
						if (sensor[2]==0) _Cube_sensor_3.transform.localScale = new Vector3(0.059f, 0.12f, 0.059f);
						if (sensor[2]==1) _Cube_sensor_3.transform.localScale = new Vector3(0.059f, 0.02f, 0.059f);
						if (sensor[3]==0) _Cube_sensor_4.transform.localScale = new Vector3(0.059f, 0.12f, 0.059f);
						if (sensor[3]==1) _Cube_sensor_4.transform.localScale = new Vector3(0.059f, 0.02f, 0.059f);		
						if (sensor[4]==0) _Cube_sensor_5.transform.localScale = new Vector3(0.059f, 0.12f, 0.059f);
						if (sensor[4]==1) _Cube_sensor_5.transform.localScale = new Vector3(0.059f, 0.02f, 0.059f);						
                        //_Cube_sensor_1.transform.localScale = new Vector3(1f, (sensor_1_i_scale), 1f);
						//_Cube_b_sensor.transform.localScale = new Vector3(1f, (b_sensor_i_scale), 1f);
                        //_Cube_sensor_12    = GameObject.Find("Cube_sensor_12");
                        //_Cube_b_sensor2    = GameObject.Find("Cube_b_sensor2");
						//sensor_1_i=100f;
						//sensor_1_i_scale=((sensor_1_i*0.01f));
						//b_sensor_i=100f;
						//b_sensor_i_scale=((b_sensor_i*0.01f));
                        //_Cube_sensor_12.transform.localScale = new Vector3(1f, (sensor_1_i_scale), 1f);
						//_Cube_b_sensor2.transform.localScale = new Vector3(1f, (b_sensor_i_scale), 1f);						
 
                    }

                }
                //catch (TimeoutException)
                catch (System.Exception)
                {
                    print("ups");
                }
				
            }
        }
		
		void ReadSerial()
		{
			try
                {

					message = sp.ReadTo("z");
					sp.DiscardInBuffer();
					string type;
					string pattern  = @"[a-z]{2}:\d{1,4}?;";  
					  
					Match m  = Regex.Match(message, pattern);
					
					while (m.Success) {
						a_sensor_c = m.Value;
						type = a_sensor_c.Substring(0,2);
						a_sensor_c = a_sensor_c.Replace(type,"");
						a_sensor_c = a_sensor_c.Replace(":","");
						a_sensor_c = a_sensor_c.Replace(";","");
						if (type.Contains("sa"))							
						{
							sensor[0] = (float)Convert.ToInt32(a_sensor_c);
							//Debug.Log("pp:" + type);							
							//Debug.Log("ok:"+a_sensor_c);
							//Debug.Log(type +":" + sensor[0].ToString());
						}
						if (type.Contains("sb"))	
						{
							sensor[1] = (float)Convert.ToInt32(a_sensor_c);	
							//Debug.Log(type.ToString() +":" + sensor[1].ToString());
						}
						if (type.Contains("sc"))	
						{
							sensor[2] = (float)Convert.ToInt32(a_sensor_c);	
							//Debug.Log(type.ToString() +":" + sensor[2].ToString());
						}
						if (type.Contains("sd"))	
						{
							sensor[3] = (float)Convert.ToInt32(a_sensor_c);	
							//Debug.Log(type.ToString() +":" + sensor[3].ToString());
						}
						if (type.Contains("se"))	
						{
							sensor[4] = (float)Convert.ToInt32(a_sensor_c);	
							//Debug.Log(type.ToString() +":" + sensor[4].ToString());
						}
						m = m.NextMatch();
					}
					
					string pattern2 = @"[a-z]{2}:.\d{1,4}.\d{1,4};";
					Match m2 = Regex.Match(message, pattern2);
					//GameObject _Text02 = GameObject.Find("Text02");
					//GameObject _Text02 = GameObject.Find("Text02").GetComponent<TextMesh>();
					TextMesh _Text01 = GameObject.Find("Text01").GetComponent<TextMesh>(); 
					TextMesh _Text02 = GameObject.Find("Text02").GetComponent<TextMesh>(); 
					TextMesh _Text03 = GameObject.Find("Text03").GetComponent<TextMesh>(); 
					//_Text02           = GameObject.Find("Text02").GetComponent<TextMesh>();
					while (m2.Success) {
						a_sensor_c = m2.Value;
						type = a_sensor_c.Substring(0,2);
						a_sensor_c = a_sensor_c.Replace(type,"");
						a_sensor_c = a_sensor_c.Replace(":","");
						a_sensor_c = a_sensor_c.Replace(";","");
						if (type.Contains("ga"))							
						{
							//gps[0] = (float)Convert.ToInt32(a_sensor_c);
							Debug.Log("ga:"+a_sensor_c);
							_Text01.text="magnetic.x:" + a_sensor_c;

						}
						if (type.Contains("gb"))							
						{
							//gps[0] = (float)Convert.ToInt32(a_sensor_c);
							Debug.Log("gb:"+a_sensor_c);
							_Text02.text="magnetic.y:" + a_sensor_c;

						}
						if (type.Contains("gc"))							
						{
							//gps[0] = (float)Convert.ToInt32(a_sensor_c);
							Debug.Log("gc:"+a_sensor_c);
							_Text03.text="magnetic.z:" + a_sensor_c;

						}
					sp.Write("y");
					m2 = m2.NextMatch();
					}					
			    }
            catch (TimeoutException)
			{
				Debug.Log("TimeoutException");
				sp.Write("y");
			}
            catch (System.Exception)
                {
                    print("ups2");
                }
		
		}
    }
//}
