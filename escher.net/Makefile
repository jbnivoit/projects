CSC=/cygdrive/e/Windows/Microsoft.NET/Framework/v2.0.50727/csc.exe /debug+

all : libs exes

clean :
	$(RM) *.dll *.exe *.pdb

libs : escher.gnu.util.dll escher.gnu.app.dll escher.gnu.x11.dll escher.gnu.app.displayhack.dll escher.gnu.x11.test.dll escher.gnu.app.redbook.dll

exes : escher.gnu.app.Salt.exe escher.gnu.app.Sniff.exe escher.gnu.app.WinOp.exe escher.gnu.app.Zion.exe escher.gnu.app.glxdemo.ABGR.exe escher.gnu.app.glxdemo.AccumBuffer.exe escher.gnu.app.glxdemo.DepthBuffer.exe escher.gnu.app.glxdemo.Line.exe escher.gnu.app.glxdemo.Point.exe escher.gnu.app.glxdemo.Primitive.exe escher.gnu.app.glxdemo.RotateBox.exe escher.gnu.app.glxdemo.StencilBuffer.exe escher.gnu.app.glxdemo.Triangle.exe escher.gnu.app.puppet.Puppet.exe escher.gnu.app.redbook.AlphaOrder.exe escher.gnu.app.redbook.AntiAliasedLine.exe escher.gnu.app.redbook.AntiAliasParallel.exe escher.gnu.app.redbook.AntiAliasPerspective.exe escher.gnu.app.redbook.BezierCurve.exe escher.gnu.app.redbook.BezierMesh.exe escher.gnu.app.redbook.BezierSurface.exe escher.gnu.app.redbook.BitmapFont.exe escher.gnu.app.redbook.BitmapLetter.exe escher.gnu.app.redbook.Clip.exe escher.gnu.app.redbook.ColorLight.exe escher.gnu.app.redbook.Cube.exe escher.gnu.app.redbook.DepthOfField.exe escher.gnu.app.redbook.DisplayList.exe escher.gnu.app.redbook.DoubleBuffer.exe escher.gnu.app.redbook.Fog.exe escher.gnu.app.redbook.GreyLight.exe escher.gnu.app.redbook.Hello.exe escher.gnu.app.redbook.Light.exe escher.gnu.app.redbook.LightPosition.exe escher.gnu.app.redbook.LineStipple.exe escher.gnu.app.redbook.MaterialColor.exe escher.gnu.app.redbook.Mipmap.exe escher.gnu.app.redbook.ModelTransform.exe escher.gnu.app.redbook.NonRectangular.exe escher.gnu.app.redbook.Pixel.exe escher.gnu.app.redbook.Planet.exe escher.gnu.app.redbook.PolygonOffset.exe escher.gnu.app.redbook.PolygonStipple.exe escher.gnu.app.redbook.Quadric.exe escher.gnu.app.redbook.Robot.exe escher.gnu.app.redbook.SmoothShade.exe escher.gnu.app.redbook.StrokeFont.exe escher.gnu.app.redbook.SubimageTexture.exe escher.gnu.app.redbook.SurfaceTexture.exe escher.gnu.app.redbook.TeapotMaterial.exe escher.gnu.app.redbook.Texture.exe escher.gnu.app.redbook.TextureBind.exe escher.gnu.app.redbook.TextureProxy.exe escher.gnu.app.redbook.TextureTeapot.exe escher.gnu.app.redbook.Torus.exe escher.gnu.app.redbook.UnProject.exe escher.gnu.app.redbook.WrapTexture.exe escher.gnu.x11.test.Blend.exe escher.gnu.x11.test.Chinese.exe escher.gnu.x11.test.DBE.exe escher.gnu.x11.test.Image.exe escher.gnu.x11.test.Hello.exe escher.gnu.x11.test.Hello2.exe escher.gnu.x11.test.Info.exe escher.gnu.x11.test.Internal.exe escher.gnu.x11.test.Polygon.exe escher.gnu.x11.test.PrintHello.exe escher.gnu.x11.test.SendEvent.exe escher.gnu.x11.test.Shape.exe escher.gnu.x11.test.Sync.exe escher.gnu.x11.test.ZPixmap.exe 

escher.gnu.util.dll : gnu\util\Math.cs gnu\util\Matrix3f.cs gnu\util\Matrix4d.cs gnu\util\Misc.cs gnu\util\Option.cs gnu\util\Vector3f.cs gnu\util\Vector4d.cs
	$(CSC) /t:library /out:escher.gnu.util.dll gnu\util\Math.cs gnu\util\Matrix3f.cs gnu\util\Matrix4d.cs gnu\util\Misc.cs gnu\util\Option.cs gnu\util\Vector3f.cs gnu\util\Vector4d.cs

escher.gnu.app.dll : gnu\app\Application.cs escher.gnu.util.dll 
	$(CSC) /t:library /out:escher.gnu.app.dll gnu\app\Application.cs /reference:escher.gnu.util.dll 

escher.gnu.x11.dll : gnu\x11\Application.cs gnu\x11\Arc.cs gnu\x11\Atom.cs gnu\x11\Color.cs gnu\x11\Colormap.cs gnu\x11\Connection.cs gnu\x11\Cursor.cs gnu\x11\Data.cs gnu\x11\Depth.cs gnu\x11\Display.cs gnu\x11\Drawable.cs gnu\x11\Enum.cs gnu\x11\Error.cs gnu\x11\xevent\Button.cs gnu\x11\xevent\ButtonPress.cs gnu\x11\xevent\ButtonRelease.cs gnu\x11\xevent\CirculateNotify.cs gnu\x11\xevent\CirculateRequest.cs gnu\x11\xevent\ClientMessage.cs gnu\x11\xevent\ColormapNotify.cs gnu\x11\xevent\ConfigureNotify.cs gnu\x11\xevent\ConfigureRequest.cs gnu\x11\xevent\CreateNotify.cs gnu\x11\xevent\DestroyNotify.cs gnu\x11\xevent\EnterNotify.cs gnu\x11\xevent\event.cs gnu\x11\xevent\Expose.cs gnu\x11\xevent\FocusIn.cs gnu\x11\xevent\FocusOut.cs gnu\x11\xevent\GraphicsExpose.cs gnu\x11\xevent\GravityNotify.cs gnu\x11\xevent\Input.cs gnu\x11\xevent\KeymapNotify.cs gnu\x11\xevent\KeyPress.cs gnu\x11\xevent\KeyRelease.cs gnu\x11\xevent\LeaveNotify.cs gnu\x11\xevent\MapNotify.cs gnu\x11\xevent\MappingNotify.cs gnu\x11\xevent\MapRequest.cs gnu\x11\xevent\MotionNotify.cs gnu\x11\xevent\NoExposure.cs gnu\x11\xevent\PropertyNotify.cs gnu\x11\xevent\ReparentNotify.cs gnu\x11\xevent\ResizeRequest.cs gnu\x11\xevent\SelectionClear.cs gnu\x11\xevent\SelectionNotify.cs gnu\x11\xevent\SelectionRequest.cs gnu\x11\xevent\UnmapNotify.cs gnu\x11\xevent\VisibilityNotify.cs gnu\x11\extension\BigRequests.cs gnu\x11\extension\DBE.cs gnu\x11\extension\DPMS.cs gnu\x11\extension\ErrorFactory.cs gnu\x11\extension\eventFactory.cs gnu\x11\extension\EVI.cs gnu\x11\extension\Extension.cs gnu\x11\extension\glx\Application.cs gnu\x11\extension\glx\Error.cs gnu\x11\extension\glx\GL.cs gnu\x11\extension\glx\GLU.cs gnu\x11\extension\glx\GLUT.cs gnu\x11\extension\glx\GLX.cs gnu\x11\extension\glx\PbufferClobberevent.cs gnu\x11\extension\glx\Pixmap.cs gnu\x11\extension\glx\Quadric.cs gnu\x11\extension\glx\VisualConfig.cs gnu\x11\extension\NotFoundException.cs gnu\x11\extension\Print.cs gnu\x11\extension\render\Color.cs gnu\x11\extension\render\ColorPoint.cs gnu\x11\extension\render\ColorSpan.cs gnu\x11\extension\render\ColorTrapezoid.cs gnu\x11\extension\render\ColorTriangle.cs gnu\x11\extension\render\GlyphSet.cs gnu\x11\extension\render\Picture.cs gnu\x11\extension\render\Quadrilateral.cs gnu\x11\extension\render\Render.cs gnu\x11\extension\render\Span.cs gnu\x11\extension\render\Trapezoid.cs gnu\x11\extension\render\Triangle.cs gnu\x11\extension\Shape.cs gnu\x11\extension\XCMisc.cs gnu\x11\extension\XTest.cs gnu\x11\Font.cs gnu\x11\Fontable.cs gnu\x11\GC.cs gnu\x11\image\Bitmap.cs gnu\x11\image\Image.cs gnu\x11\image\PPM.cs gnu\x11\image\XBM.cs gnu\x11\image\XPM.cs gnu\x11\image\ZPixmap.cs gnu\x11\Input.cs gnu\x11\keysym\APL.cs gnu\x11\keysym\Apollo.cs gnu\x11\keysym\Arabic.cs gnu\x11\keysym\Armenian.cs gnu\x11\keysym\Caucasus.cs gnu\x11\keysym\Currency.cs gnu\x11\keysym\Cyrillic.cs gnu\x11\keysym\DEC.cs gnu\x11\keysym\Georgian.cs gnu\x11\keysym\Greek.cs gnu\x11\keysym\Hebrew.cs gnu\x11\keysym\HP.cs gnu\x11\keysym\Katakana.cs gnu\x11\keysym\Korean.cs gnu\x11\keysym\Latin1.cs gnu\x11\keysym\Latin2.cs gnu\x11\keysym\Latin3.cs gnu\x11\keysym\Latin4.cs gnu\x11\keysym\Latin8.cs gnu\x11\keysym\Latin9.cs gnu\x11\keysym\Misc.cs gnu\x11\keysym\OSF.cs gnu\x11\keysym\Publishing.cs gnu\x11\keysym\Special.cs gnu\x11\keysym\Sun.cs gnu\x11\keysym\T3270.cs gnu\x11\keysym\Technical.cs gnu\x11\keysym\Thai.cs gnu\x11\keysym\Vietnamese.cs gnu\x11\keysym\XFree86.cs gnu\x11\keysym\XKB.cs gnu\x11\MessageFactory.cs gnu\x11\Option.cs gnu\x11\Pixmap.cs gnu\x11\Point.cs gnu\x11\Rectangle.cs gnu\x11\Request.cs gnu\x11\Resource.cs gnu\x11\RGB.cs gnu\x11\Screen.cs gnu\x11\Segment.cs gnu\x11\Size.cs gnu\x11\Text.cs gnu\x11\ValueList.cs gnu\x11\Visual.cs gnu\x11\Window.cs
	$(CSC) /t:library /out:escher.gnu.x11.dll /reference:escher.gnu.util.dll /reference:escher.gnu.app.dll gnu\x11\Application.cs gnu\x11\Arc.cs gnu\x11\Atom.cs gnu\x11\Color.cs gnu\x11\Colormap.cs gnu\x11\Connection.cs gnu\x11\Cursor.cs gnu\x11\Data.cs gnu\x11\Depth.cs gnu\x11\Display.cs gnu\x11\Drawable.cs gnu\x11\Enum.cs gnu\x11\Error.cs gnu\x11\xevent\Button.cs gnu\x11\xevent\ButtonPress.cs gnu\x11\xevent\ButtonRelease.cs gnu\x11\xevent\CirculateNotify.cs gnu\x11\xevent\CirculateRequest.cs gnu\x11\xevent\ClientMessage.cs gnu\x11\xevent\ColormapNotify.cs gnu\x11\xevent\ConfigureNotify.cs gnu\x11\xevent\ConfigureRequest.cs gnu\x11\xevent\CreateNotify.cs gnu\x11\xevent\DestroyNotify.cs gnu\x11\xevent\EnterNotify.cs gnu\x11\xevent\event.cs gnu\x11\xevent\Expose.cs gnu\x11\xevent\FocusIn.cs gnu\x11\xevent\FocusOut.cs gnu\x11\xevent\GraphicsExpose.cs gnu\x11\xevent\GravityNotify.cs gnu\x11\xevent\Input.cs gnu\x11\xevent\KeymapNotify.cs gnu\x11\xevent\KeyPress.cs gnu\x11\xevent\KeyRelease.cs gnu\x11\xevent\LeaveNotify.cs gnu\x11\xevent\MapNotify.cs gnu\x11\xevent\MappingNotify.cs gnu\x11\xevent\MapRequest.cs gnu\x11\xevent\MotionNotify.cs gnu\x11\xevent\NoExposure.cs gnu\x11\xevent\PropertyNotify.cs gnu\x11\xevent\ReparentNotify.cs gnu\x11\xevent\ResizeRequest.cs gnu\x11\xevent\SelectionClear.cs gnu\x11\xevent\SelectionNotify.cs gnu\x11\xevent\SelectionRequest.cs gnu\x11\xevent\UnmapNotify.cs gnu\x11\xevent\VisibilityNotify.cs gnu\x11\extension\BigRequests.cs gnu\x11\extension\DBE.cs gnu\x11\extension\DPMS.cs gnu\x11\extension\ErrorFactory.cs gnu\x11\extension\eventFactory.cs gnu\x11\extension\EVI.cs gnu\x11\extension\Extension.cs gnu\x11\extension\glx\Application.cs gnu\x11\extension\glx\Error.cs gnu\x11\extension\glx\GL.cs gnu\x11\extension\glx\GLU.cs gnu\x11\extension\glx\GLUT.cs gnu\x11\extension\glx\GLX.cs gnu\x11\extension\glx\PbufferClobberevent.cs gnu\x11\extension\glx\Pixmap.cs gnu\x11\extension\glx\Quadric.cs gnu\x11\extension\glx\VisualConfig.cs gnu\x11\extension\NotFoundException.cs gnu\x11\extension\Print.cs gnu\x11\extension\render\Color.cs gnu\x11\extension\render\ColorPoint.cs gnu\x11\extension\render\ColorSpan.cs gnu\x11\extension\render\ColorTrapezoid.cs gnu\x11\extension\render\ColorTriangle.cs gnu\x11\extension\render\GlyphSet.cs gnu\x11\extension\render\Picture.cs gnu\x11\extension\render\Quadrilateral.cs gnu\x11\extension\render\Render.cs gnu\x11\extension\render\Span.cs gnu\x11\extension\render\Trapezoid.cs gnu\x11\extension\render\Triangle.cs gnu\x11\extension\Shape.cs gnu\x11\extension\XCMisc.cs gnu\x11\extension\XTest.cs gnu\x11\Font.cs gnu\x11\Fontable.cs gnu\x11\GC.cs gnu\x11\image\Bitmap.cs gnu\x11\image\Image.cs gnu\x11\image\PPM.cs gnu\x11\image\XBM.cs gnu\x11\image\XPM.cs gnu\x11\image\ZPixmap.cs gnu\x11\Input.cs gnu\x11\keysym\APL.cs gnu\x11\keysym\Apollo.cs gnu\x11\keysym\Arabic.cs gnu\x11\keysym\Armenian.cs gnu\x11\keysym\Caucasus.cs gnu\x11\keysym\Currency.cs gnu\x11\keysym\Cyrillic.cs gnu\x11\keysym\DEC.cs gnu\x11\keysym\Georgian.cs gnu\x11\keysym\Greek.cs gnu\x11\keysym\Hebrew.cs gnu\x11\keysym\HP.cs gnu\x11\keysym\Katakana.cs gnu\x11\keysym\Korean.cs gnu\x11\keysym\Latin1.cs gnu\x11\keysym\Latin2.cs gnu\x11\keysym\Latin3.cs gnu\x11\keysym\Latin4.cs gnu\x11\keysym\Latin8.cs gnu\x11\keysym\Latin9.cs gnu\x11\keysym\Misc.cs gnu\x11\keysym\OSF.cs gnu\x11\keysym\Publishing.cs gnu\x11\keysym\Special.cs gnu\x11\keysym\Sun.cs gnu\x11\keysym\T3270.cs gnu\x11\keysym\Technical.cs gnu\x11\keysym\Thai.cs gnu\x11\keysym\Vietnamese.cs gnu\x11\keysym\XFree86.cs gnu\x11\keysym\XKB.cs gnu\x11\MessageFactory.cs gnu\x11\Option.cs gnu\x11\Pixmap.cs gnu\x11\Point.cs gnu\x11\Rectangle.cs gnu\x11\Request.cs gnu\x11\Resource.cs gnu\x11\RGB.cs gnu\x11\Screen.cs gnu\x11\Segment.cs gnu\x11\Size.cs gnu\x11\Text.cs gnu\x11\ValueList.cs gnu\x11\Visual.cs gnu\x11\Window.cs

escher.gnu.app.displayhack.dll : gnu\app\displayhack\DisplayHack.cs gnu\app\displayhack\eraser\Circle.cs gnu\app\displayhack\eraser\Clear.cs gnu\app\displayhack\eraser\Eraser.cs gnu\app\displayhack\eraser\SlideLines.cs gnu\app\displayhack\eraser\ThreeCircles.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll
	$(CSC) /t:library /out:escher.gnu.app.displayhack.dll gnu\app\displayhack\DisplayHack.cs gnu\app\displayhack\eraser\Circle.cs gnu\app\displayhack\eraser\Clear.cs gnu\app\displayhack\eraser\Eraser.cs gnu\app\displayhack\eraser\SlideLines.cs gnu\app\displayhack\eraser\ThreeCircles.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll

escher.gnu.x11.test.dll : gnu\x11\test\Graphics.cs
	$(CSC) /t:library /out:escher.gnu.x11.test.dll /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll gnu\x11\test\Graphics.cs

escher.gnu.app.redbook.dll : gnu\app\redbook\AntiAlias.cs gnu\app\redbook\Checkerboard.cs gnu\app\redbook\Jitter.cs gnu\app\redbook\Teapot.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll
	$(CSC) /t:library /out:escher.gnu.app.redbook.dll gnu\app\redbook\AntiAlias.cs gnu\app\redbook\Checkerboard.cs gnu\app\redbook\Jitter.cs gnu\app\redbook\Teapot.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll



escher.gnu.app.displayhack.Deco.exe : gnu\app\displayhack\Deco.cs escher.gnu.app.displayhack.dll
	$(CSC) /out:escher.gnu.app.displayhack.Deco.exe /t:exe gnu\app\displayhack\Deco.cs /reference:escher.gnu.app.displayhack.dll

escher.gnu.app.displayhack.Munch.exe : gnu\app\displayhack\Munch.cs escher.gnu.app.displayhack.dll
	$(CSC) /out:escher.gnu.app.displayhack.Munch.exe /t:exe gnu\app\displayhack\Munch.cs /reference:escher.gnu.app.displayhack.dll

escher.gnu.app.displayhack.Rorschach.exe : gnu\app\displayhack\Rorschach.cs escher.gnu.app.displayhack.dll
	$(CSC) /out:escher.gnu.app.displayhack.Rorschach.exe /t:exe gnu\app\displayhack\Rorschach.cs /reference:escher.gnu.app.displayhack.dll

escher.gnu.app.displayhack.Sprites.exe : gnu\app\displayhack\Sprites.cs escher.gnu.app.displayhack.dll
	$(CSC) /out:escher.gnu.app.displayhack.Sprites.exe /t:exe gnu\app\displayhack\Sprites.cs /reference:escher.gnu.app.displayhack.dll

escher.gnu.app.displayhack.Squiral.exe : gnu\app\displayhack\Squiral.cs escher.gnu.app.displayhack.dll
	$(CSC) /out:escher.gnu.app.displayhack.Squiral.exe /t:exe gnu\app\displayhack\Squiral.cs /reference:escher.gnu.app.displayhack.dll


escher.gnu.app.Salt.exe : gnu\app\Salt.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll
	$(CSC) /t:exe /out:escher.gnu.app.Salt.exe gnu\app\Salt.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll

escher.gnu.app.Sniff.exe : gnu\app\Sniff.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll
	$(CSC) /t:exe /out:escher.gnu.app.Sniff.exe gnu\app\Sniff.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll

escher.gnu.app.WinOp.exe : gnu\app\WinOp.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll
	$(CSC) /t:exe /out:escher.gnu.app.WinOp.exe gnu\app\WinOp.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll

escher.gnu.app.Zion.exe : gnu\app\Zion.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll
	$(CSC) /t:exe /out:escher.gnu.app.Zion.exe gnu\app\Zion.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll

escher.gnu.app.glxdemo.ABGR.exe : gnu\app\glxdemo\ABGR.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.app.redbook.dll
	$(CSC) /t:exe /out:escher.gnu.app.glxdemo.ABGR.exe gnu\app\glxdemo\ABGR.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.app.redbook.dll

escher.gnu.app.glxdemo.AccumBuffer.exe : gnu\app\glxdemo\AccumBuffer.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.app.redbook.dll
	$(CSC) /t:exe /out:escher.gnu.app.glxdemo.AccumBuffer.exe gnu\app\glxdemo\AccumBuffer.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.app.redbook.dll

escher.gnu.app.glxdemo.DepthBuffer.exe : gnu\app\glxdemo\DepthBuffer.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.app.redbook.dll
	$(CSC) /t:exe /out:escher.gnu.app.glxdemo.DepthBuffer.exe gnu\app\glxdemo\DepthBuffer.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.app.redbook.dll

escher.gnu.app.glxdemo.Line.exe : gnu\app\glxdemo\Line.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.app.redbook.dll
	$(CSC) /t:exe /out:escher.gnu.app.glxdemo.Line.exe gnu\app\glxdemo\Line.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.app.redbook.dll

escher.gnu.app.glxdemo.Point.exe : gnu\app\glxdemo\Point.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.app.redbook.dll
	$(CSC) /t:exe /out:escher.gnu.app.glxdemo.Point.exe gnu\app\glxdemo\Point.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.app.redbook.dll

escher.gnu.app.glxdemo.Primitive.exe : gnu\app\glxdemo\Primitive.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.app.redbook.dll
	$(CSC) /t:exe /out:escher.gnu.app.glxdemo.Primitive.exe gnu\app\glxdemo\Primitive.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.app.redbook.dll

escher.gnu.app.glxdemo.RotateBox.exe : gnu\app\glxdemo\RotateBox.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.app.redbook.dll
	$(CSC) /t:exe /out:escher.gnu.app.glxdemo.RotateBox.exe gnu\app\glxdemo\RotateBox.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.app.redbook.dll

escher.gnu.app.glxdemo.StencilBuffer.exe : gnu\app\glxdemo\StencilBuffer.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.app.redbook.dll
	$(CSC) /t:exe /out:escher.gnu.app.glxdemo.StencilBuffer.exe gnu\app\glxdemo\StencilBuffer.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.app.redbook.dll

escher.gnu.app.glxdemo.Triangle.exe : gnu\app\glxdemo\Triangle.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.app.redbook.dll
	$(CSC) /t:exe /out:escher.gnu.app.glxdemo.Triangle.exe gnu\app\glxdemo\Triangle.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.app.redbook.dll

escher.gnu.app.puppet.Puppet.exe : gnu\app\puppet\Puppet.cs gnu\app\puppet\Client.cs gnu\app\puppet\Preference.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.app.redbook.dll
	$(CSC) /t:exe /out:escher.gnu.app.puppet.Puppet.exe gnu\app\puppet\Puppet.cs gnu\app\puppet\Client.cs gnu\app\puppet\Preference.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.app.redbook.dll

escher.gnu.app.redbook.AlphaOrder.exe : gnu\app\redbook\AlphaOrder.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.app.redbook.dll
	$(CSC) /t:exe /out:escher.gnu.app.redbook.AlphaOrder.exe gnu\app\redbook\AlphaOrder.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.app.redbook.dll

escher.gnu.app.redbook.AntiAliasedLine.exe : gnu\app\redbook\AntiAliasedLine.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.app.redbook.dll
	$(CSC) /t:exe /out:escher.gnu.app.redbook.AntiAliasedLine.exe gnu\app\redbook\AntiAliasedLine.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.app.redbook.dll

escher.gnu.app.redbook.AntiAliasParallel.exe : gnu\app\redbook\AntiAliasParallel.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.app.redbook.dll
	$(CSC) /t:exe /out:escher.gnu.app.redbook.AntiAliasParallel.exe gnu\app\redbook\AntiAliasParallel.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.app.redbook.dll

escher.gnu.app.redbook.AntiAliasPerspective.exe : gnu\app\redbook\AntiAliasPerspective.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.app.redbook.dll
	$(CSC) /t:exe /out:escher.gnu.app.redbook.AntiAliasPerspective.exe gnu\app\redbook\AntiAliasPerspective.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.app.redbook.dll

escher.gnu.app.redbook.BezierCurve.exe : gnu\app\redbook\BezierCurve.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.app.redbook.dll
	$(CSC) /t:exe /out:escher.gnu.app.redbook.BezierCurve.exe gnu\app\redbook\BezierCurve.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.app.redbook.dll

escher.gnu.app.redbook.BezierMesh.exe : gnu\app\redbook\BezierMesh.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.app.redbook.dll
	$(CSC) /t:exe /out:escher.gnu.app.redbook.BezierMesh.exe gnu\app\redbook\BezierMesh.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.app.redbook.dll

escher.gnu.app.redbook.BezierSurface.exe : gnu\app\redbook\BezierSurface.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.app.redbook.dll
	$(CSC) /t:exe /out:escher.gnu.app.redbook.BezierSurface.exe gnu\app\redbook\BezierSurface.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.app.redbook.dll

escher.gnu.app.redbook.BitmapFont.exe : gnu\app\redbook\BitmapFont.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.app.redbook.dll
	$(CSC) /t:exe /out:escher.gnu.app.redbook.BitmapFont.exe gnu\app\redbook\BitmapFont.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.app.redbook.dll

escher.gnu.app.redbook.BitmapLetter.exe : gnu\app\redbook\BitmapLetter.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.app.redbook.dll
	$(CSC) /t:exe /out:escher.gnu.app.redbook.BitmapLetter.exe gnu\app\redbook\BitmapLetter.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.app.redbook.dll

escher.gnu.app.redbook.Clip.exe : gnu\app\redbook\Clip.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.app.redbook.dll
	$(CSC) /t:exe /out:escher.gnu.app.redbook.Clip.exe gnu\app\redbook\Clip.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.app.redbook.dll

escher.gnu.app.redbook.ColorLight.exe : gnu\app\redbook\ColorLight.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.app.redbook.dll
	$(CSC) /t:exe /out:escher.gnu.app.redbook.ColorLight.exe gnu\app\redbook\ColorLight.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.app.redbook.dll

escher.gnu.app.redbook.Cube.exe : gnu\app\redbook\Cube.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.app.redbook.dll
	$(CSC) /t:exe /out:escher.gnu.app.redbook.Cube.exe gnu\app\redbook\Cube.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.app.redbook.dll

escher.gnu.app.redbook.DepthOfField.exe : gnu\app\redbook\DepthOfField.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.app.redbook.dll
	$(CSC) /t:exe /out:escher.gnu.app.redbook.DepthOfField.exe gnu\app\redbook\DepthOfField.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.app.redbook.dll

escher.gnu.app.redbook.DisplayList.exe : gnu\app\redbook\DisplayList.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.app.redbook.dll
	$(CSC) /t:exe /out:escher.gnu.app.redbook.DisplayList.exe gnu\app\redbook\DisplayList.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.app.redbook.dll

escher.gnu.app.redbook.DoubleBuffer.exe : gnu\app\redbook\DoubleBuffer.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.app.redbook.dll
	$(CSC) /t:exe /out:escher.gnu.app.redbook.DoubleBuffer.exe gnu\app\redbook\DoubleBuffer.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.app.redbook.dll

escher.gnu.app.redbook.Fog.exe : gnu\app\redbook\Fog.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.app.redbook.dll
	$(CSC) /t:exe /out:escher.gnu.app.redbook.Fog.exe gnu\app\redbook\Fog.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.app.redbook.dll

escher.gnu.app.redbook.GreyLight.exe : gnu\app\redbook\GreyLight.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.app.redbook.dll
	$(CSC) /t:exe /out:escher.gnu.app.redbook.GreyLight.exe gnu\app\redbook\GreyLight.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.app.redbook.dll

escher.gnu.app.redbook.Hello.exe : gnu\app\redbook\Hello.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.app.redbook.dll
	$(CSC) /t:exe /out:escher.gnu.app.redbook.Hello.exe gnu\app\redbook\Hello.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.app.redbook.dll

escher.gnu.app.redbook.Light.exe : gnu\app\redbook\Light.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.app.redbook.dll
	$(CSC) /t:exe /out:escher.gnu.app.redbook.Light.exe gnu\app\redbook\Light.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.app.redbook.dll

escher.gnu.app.redbook.LightPosition.exe : gnu\app\redbook\LightPosition.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.app.redbook.dll
	$(CSC) /t:exe /out:escher.gnu.app.redbook.LightPosition.exe gnu\app\redbook\LightPosition.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.app.redbook.dll

escher.gnu.app.redbook.LineStipple.exe : gnu\app\redbook\LineStipple.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.app.redbook.dll
	$(CSC) /t:exe /out:escher.gnu.app.redbook.LineStipple.exe gnu\app\redbook\LineStipple.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.app.redbook.dll

escher.gnu.app.redbook.MaterialColor.exe : gnu\app\redbook\MaterialColor.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.app.redbook.dll
	$(CSC) /t:exe /out:escher.gnu.app.redbook.MaterialColor.exe gnu\app\redbook\MaterialColor.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.app.redbook.dll

escher.gnu.app.redbook.Mipmap.exe : gnu\app\redbook\Mipmap.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.app.redbook.dll
	$(CSC) /t:exe /out:escher.gnu.app.redbook.Mipmap.exe gnu\app\redbook\Mipmap.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.app.redbook.dll

escher.gnu.app.redbook.ModelTransform.exe : gnu\app\redbook\ModelTransform.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.app.redbook.dll
	$(CSC) /t:exe /out:escher.gnu.app.redbook.ModelTransform.exe gnu\app\redbook\ModelTransform.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.app.redbook.dll

escher.gnu.app.redbook.NonRectangular.exe : gnu\app\redbook\NonRectangular.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.app.redbook.dll
	$(CSC) /t:exe /out:escher.gnu.app.redbook.NonRectangular.exe gnu\app\redbook\NonRectangular.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.app.redbook.dll

escher.gnu.app.redbook.Pixel.exe : gnu\app\redbook\Pixel.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.app.redbook.dll
	$(CSC) /t:exe /out:escher.gnu.app.redbook.Pixel.exe gnu\app\redbook\Pixel.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.app.redbook.dll

escher.gnu.app.redbook.Planet.exe : gnu\app\redbook\Planet.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.app.redbook.dll
	$(CSC) /t:exe /out:escher.gnu.app.redbook.Planet.exe gnu\app\redbook\Planet.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.app.redbook.dll

escher.gnu.app.redbook.PolygonOffset.exe : gnu\app\redbook\PolygonOffset.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.app.redbook.dll
	$(CSC) /t:exe /out:escher.gnu.app.redbook.PolygonOffset.exe gnu\app\redbook\PolygonOffset.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.app.redbook.dll

escher.gnu.app.redbook.PolygonStipple.exe : gnu\app\redbook\PolygonStipple.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.app.redbook.dll
	$(CSC) /t:exe /out:escher.gnu.app.redbook.PolygonStipple.exe gnu\app\redbook\PolygonStipple.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.app.redbook.dll

escher.gnu.app.redbook.Quadric.exe : gnu\app\redbook\Quadric.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.app.redbook.dll
	$(CSC) /t:exe /out:escher.gnu.app.redbook.Quadric.exe gnu\app\redbook\Quadric.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.app.redbook.dll

escher.gnu.app.redbook.Robot.exe : gnu\app\redbook\Robot.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.app.redbook.dll
	$(CSC) /t:exe /out:escher.gnu.app.redbook.Robot.exe gnu\app\redbook\Robot.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.app.redbook.dll

escher.gnu.app.redbook.SmoothShade.exe : gnu\app\redbook\SmoothShade.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.app.redbook.dll
	$(CSC) /t:exe /out:escher.gnu.app.redbook.SmoothShade.exe gnu\app\redbook\SmoothShade.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.app.redbook.dll

escher.gnu.app.redbook.StrokeFont.exe : gnu\app\redbook\StrokeFont.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.app.redbook.dll
	$(CSC) /t:exe /out:escher.gnu.app.redbook.StrokeFont.exe gnu\app\redbook\StrokeFont.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.app.redbook.dll

escher.gnu.app.redbook.SubimageTexture.exe : gnu\app\redbook\SubimageTexture.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.app.redbook.dll
	$(CSC) /t:exe /out:escher.gnu.app.redbook.SubimageTexture.exe gnu\app\redbook\SubimageTexture.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.app.redbook.dll

escher.gnu.app.redbook.SurfaceTexture.exe : gnu\app\redbook\SurfaceTexture.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.app.redbook.dll
	$(CSC) /t:exe /out:escher.gnu.app.redbook.SurfaceTexture.exe gnu\app\redbook\SurfaceTexture.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.app.redbook.dll

escher.gnu.app.redbook.TeapotMaterial.exe : gnu\app\redbook\TeapotMaterial.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.app.redbook.dll
	$(CSC) /t:exe /out:escher.gnu.app.redbook.TeapotMaterial.exe gnu\app\redbook\TeapotMaterial.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.app.redbook.dll

escher.gnu.app.redbook.Texture.exe : gnu\app\redbook\Texture.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.app.redbook.dll
	$(CSC) /t:exe /out:escher.gnu.app.redbook.Texture.exe gnu\app\redbook\Texture.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.app.redbook.dll

escher.gnu.app.redbook.TextureBind.exe : gnu\app\redbook\TextureBind.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.app.redbook.dll
	$(CSC) /t:exe /out:escher.gnu.app.redbook.TextureBind.exe gnu\app\redbook\TextureBind.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.app.redbook.dll

escher.gnu.app.redbook.TextureProxy.exe : gnu\app\redbook\TextureProxy.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.app.redbook.dll
	$(CSC) /t:exe /out:escher.gnu.app.redbook.TextureProxy.exe gnu\app\redbook\TextureProxy.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.app.redbook.dll

escher.gnu.app.redbook.TextureTeapot.exe : gnu\app\redbook\TextureTeapot.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.app.redbook.dll
	$(CSC) /t:exe /out:escher.gnu.app.redbook.TextureTeapot.exe gnu\app\redbook\TextureTeapot.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.app.redbook.dll

escher.gnu.app.redbook.Torus.exe : gnu\app\redbook\Torus.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.app.redbook.dll
	$(CSC) /t:exe /out:escher.gnu.app.redbook.Torus.exe gnu\app\redbook\Torus.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.app.redbook.dll

escher.gnu.app.redbook.UnProject.exe : gnu\app\redbook\UnProject.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.app.redbook.dll
	$(CSC) /t:exe /out:escher.gnu.app.redbook.UnProject.exe gnu\app\redbook\UnProject.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.app.redbook.dll

escher.gnu.app.redbook.WrapTexture.exe : gnu\app\redbook\WrapTexture.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.app.redbook.dll
	$(CSC) /t:exe /out:escher.gnu.app.redbook.WrapTexture.exe gnu\app\redbook\WrapTexture.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.app.redbook.dll

escher.gnu.x11.test.Blend.exe : gnu\x11\test\Blend.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.x11.test.dll
	$(CSC) /t:exe /out:escher.gnu.x11.test.Blend.exe gnu\x11\test\Blend.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.x11.test.dll

escher.gnu.x11.test.Chinese.exe : gnu\x11\test\Chinese.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.x11.test.dll
	$(CSC) /t:exe /out:escher.gnu.x11.test.Chinese.exe gnu\x11\test\Chinese.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.x11.test.dll

escher.gnu.x11.test.DBE.exe : gnu\x11\test\DBE.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.x11.test.dll
	$(CSC) /t:exe /out:escher.gnu.x11.test.DBE.exe gnu\x11\test\DBE.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.x11.test.dll

escher.gnu.x11.test.Image.exe : gnu\x11\test\Image.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.x11.test.dll
	$(CSC) /t:exe /out:escher.gnu.x11.test.Image.exe gnu\x11\test\Image.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.x11.test.dll

escher.gnu.x11.test.Hello.exe : gnu\x11\test\Hello.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.x11.test.dll
	$(CSC) /t:exe /out:escher.gnu.x11.test.Hello.exe gnu\x11\test\Hello.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.x11.test.dll

escher.gnu.x11.test.Hello2.exe : gnu\x11\test\Hello2.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.x11.test.dll
	$(CSC) /t:exe /out:escher.gnu.x11.test.Hello2.exe gnu\x11\test\Hello2.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.x11.test.dll

escher.gnu.x11.test.Info.exe : gnu\x11\test\Info.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.x11.test.dll
	$(CSC) /t:exe /out:escher.gnu.x11.test.Info.exe gnu\x11\test\Info.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.x11.test.dll

escher.gnu.x11.test.Internal.exe : gnu\x11\test\Internal.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.x11.test.dll
	$(CSC) /t:exe /out:escher.gnu.x11.test.Internal.exe gnu\x11\test\Internal.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.x11.test.dll

escher.gnu.x11.test.Polygon.exe : gnu\x11\test\Polygon.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.x11.test.dll
	$(CSC) /t:exe /out:escher.gnu.x11.test.Polygon.exe gnu\x11\test\Polygon.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.x11.test.dll

escher.gnu.x11.test.PrintHello.exe : gnu\x11\test\PrintHello.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.x11.test.dll
	$(CSC) /t:exe /out:escher.gnu.x11.test.PrintHello.exe gnu\x11\test\PrintHello.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.x11.test.dll

escher.gnu.x11.test.SendEvent.exe : gnu\x11\test\SendEvent.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.x11.test.dll
	$(CSC) /t:exe /out:escher.gnu.x11.test.SendEvent.exe gnu\x11\test\SendEvent.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.x11.test.dll

escher.gnu.x11.test.Shape.exe : gnu\x11\test\Shape.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.x11.test.dll
	$(CSC) /t:exe /out:escher.gnu.x11.test.Shape.exe gnu\x11\test\Shape.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.x11.test.dll

escher.gnu.x11.test.Sync.exe : gnu\x11\test\Sync.cs escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.x11.test.dll
	$(CSC) /t:exe /out:escher.gnu.x11.test.Sync.exe gnu\x11\test\Sync.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.x11.test.dll

escher.gnu.x11.test.ZPixmap.exe : gnu\x11\test\ZPixmap.cs  escher.gnu.x11.dll escher.gnu.app.dll escher.gnu.util.dll escher.gnu.x11.test.dll
	$(CSC) /t:exe /out:escher.gnu.x11.test.ZPixmap.exe gnu\x11\test\ZPixmap.cs /reference:escher.gnu.x11.dll /reference:escher.gnu.app.dll /reference:escher.gnu.util.dll /reference:escher.gnu.x11.test.dll
