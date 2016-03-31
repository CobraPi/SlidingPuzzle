#version 430

in vec3 instancePos;
in vec3 position;
in vec4 color;
in vec2 uvCoords;
in int gl_InstanceID;

uniform int size;
uniform mat4 modelMatrix;
uniform mat4 viewProjMatrix;

flat out int instance;
out vec2 fuvCoords;
out vec4 fcolor;

void main() {
    vec3 realPos = position + instancePos;
    gl_Position = viewProjMatrix * modelMatrix * vec4(realPos, 1);

    int row = gl_InstanceID%size;
    int col = gl_InstanceID/size;

    float floatSize = size;
    float increment = 1/floatSize;

    if (uvCoords.s == 0)
    {
        fuvCoords.s = increment * col;
    }
    else if (uvCoords.s == 1)
    {
        fuvCoords.s = increment * col + increment;
    }

    if (uvCoords.t == 0)
    {
        fuvCoords.t = increment * row;
    }
    else if (uvCoords.t == 1)
    {
        fuvCoords.t = increment * row + increment;
    }

    instance = gl_InstanceID;

    fcolor = vec4(1,1,1,1);
}
