float circle(in vec2 _st, in float _radius) {
    vec2 dist = _st-vec2(0.5);
	return 1.-smoothstep(_radius-(_radius*0.01),
                         _radius+(_radius*0.01),
                         dot(dist,dist)*4.0);
}

vec2 tile (vec2 _st, float _zoom) {
    _st *= _zoom;
    return fract(_st);
}

void main(){
	vec2 st = gl_FragCoord.xy / iResolution.xy;
    st = tile(st,5.0);

    vec3 color = vec3(circle(st,0.6));

	gl_FragColor = vec4( color, 1.0 );
}