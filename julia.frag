
uniform vec2 res;
uniform float zoom;
uniform float centerX;
uniform float centerY;
uniform float isColor;

float map(float xy, float a, float b, float c, float d)
{
    return (xy - a) * ((d-c) / (b-a)) + c;
}

void main()
{
    vec3 col = vec3(0.0);

	vec2 coord = gl_FragCoord.xy;
    
    float width = pow(2.0, (2.0 - zoom));
    float height = (res.y / res.x) * width;

    float tx = -(width / 2.0) + centerX;
    float tx2 = (width / 2.0) + centerX;

    float ty = -(height / 2.0) + centerY;
    float ty2 = (height / 2.0) + centerY;

    float scaled_x = map(coord.x, 0.0, res.x, tx, tx2);
    float scaled_y = map(coord.y, 0.0, res.y, ty, ty2);

    float c_x = scaled_x;
    float c_y = scaled_y;

    float n = 0.0;

    while((n < 1000.0) && ((scaled_x * scaled_x + scaled_y * scaled_y) < 4.0))
    {
        float real = scaled_x * scaled_x - scaled_y * scaled_y;
        float img = 2.0 * scaled_x * scaled_y;

        scaled_x = real + centerX;
        scaled_y = img + centerY;
        n++;
    }

    float grayscale = map(n, 0.0, 1000.0, 0.0, 1.0);


    if(isColor == 1.0)
    {
        col += 0.5 + cos( 3.0 + n*0.15 + vec3(0.0,0.6,1.0));
        gl_FragColor = vec4(col, 1.0);
    }
    else
    {
        gl_FragColor = vec4(grayscale, grayscale, grayscale, 1.0);
    }
}