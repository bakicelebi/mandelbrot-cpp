
uniform vec2 res;
uniform float zoom;
uniform float centerX;
uniform float centerY;

float map(float xy, float a, float b, float c, float d)
{
    return (xy - a) * ((d-c) / (b-a)) + c;
}

void main()
{
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

    int n = 0;

    while((n < 1000) && ((scaled_x * scaled_x + scaled_y * scaled_y) < 4.0))
    {
        float real = scaled_x * scaled_x - scaled_y * scaled_y;
        float img = 2.0 * scaled_x * scaled_y;

        scaled_x = real + c_x;
        scaled_y = img + c_y;
        n++;
    }

    float grayscale = map(float(n), 0.0, 1000.0, 0.0, 1.0);
    if(n < 1000) 
    {
        gl_FragColor = vec4(grayscale, grayscale, grayscale, 1.0);
    }
    else
    {
        gl_FragColor = vec4(grayscale, grayscale, grayscale, 1.0);
    }
}