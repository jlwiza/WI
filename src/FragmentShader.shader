 R"(

			#version 330 core

			layout(location = 0)out vec4 color;
			//in vec2 v_textCoord;
			in vec4 fragmentColor;

			//layout(location = 0)out vec4 testColor;


			//uniform sampler2D u_Texture;
			void main(){
			//vec4 texColor = texture(u_Texture,v_textCoord);
			//color = vec4(0.0,0.0,0.0,1.0);
			//color = texColor; 
			color = fragmentColor;
			}



			)";