using gnu.x11;

namespace gnu.x11.extension.render {


/** GlyphSet in RENDER. */
public class GlyphSet : gnu.x11.Resource {
  public Render render;

 
  // render opcode 17 - create glyph set
  /**
   * @see <a href="XRenderCreateGlyphSet.html">XRenderCreateGlyphSet</a>
   */
  public GlyphSet (Render render, Picture.Format format)
    : base (render.display) {
    this.render = render;

    Request request = new Request (display, render.major_opcode, 17, 3);
    request.write4 (id);
    request.write4 (format.id ());
    display.send_request (request);
  }


  // render opcode 18 - reference glyph set
  /**
   * @see <a href="XRenderReferenceGlyphSet.html">
   * XRenderReferenceGlyphSet</a>
   */
  public GlyphSet (GlyphSet src)
    : base (src.display) {
    render = src.render;

    Request request = new Request (display, render.major_opcode, 18, 3);
    request.write4 (id);
    request.write4 (src.id);
    display.send_request (request);
  }


  // render opcode 19 - free glyph set
  /**
   * @see <a href="XRenderFreeGlyphSet.html">XRenderFreeGlyphSet</a>
   */
  public void free () {
    Request request = new Request (display, render.major_opcode, 19, 2);
    request.write4 (id);
    display.send_request (request);
  }
}

}
