#version 450

// We will draw patches of 16*16 pixels, 80*45 times for a final 1280*720 image
layout (local_size_x = 16, local_size_y = 16) in;

// No data input: the compute shader will create the image output.
layout (rgba32f, binding = 0) uniform image2D img_output;

void main() {
  // gl_LocalInvocationID.xy * gl_WorkGroupID.xy == gl_GlobalInvocationID
  ivec2 coords = ivec2(gl_GlobalInvocationID);

  // We want to draw an orange and blue grid 
  vec4 pixel;
  // Orange alternance: when workgroup x is even we want workgroup y to be odd, and vice-versa
  if ( ((gl_WorkGroupID.x & 1u) != 1u) != ((gl_WorkGroupID.y & 1u) == 1u)) {
    pixel = vec4(1.0,.5,.0,1.0);
  }
  // Blue alternance in case orange condition is not met
  else {
    pixel = vec4(.0,.5,1.0,1.0);
  }

  imageStore(img_output, coords, pixel);
}