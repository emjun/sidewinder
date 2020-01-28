/* The problem with my current layout stuff is that I can't agree on whether the center is at the
   top or the middle of the space! */
/* NOTE: everything should be rendered so that its bounding box starts at the origin in the top left
   corner. */
open Theia;

let a = str("2");
let a' = box(~dx=(12.5 -. 9.) /. 2. +. 2.5 /. 2., ~dy=2.5 /. 2., [a], []);

let b =
  atom(
    ~links=[],
    <circle r="2" cx="2" cy="2" />,
    Rectangle.fromPointSize(~x=0., ~y=0., ~width=4., ~height=4.),
  );
let b' =
  box(
    ~dx=11. /. 2.,
    ~dy=11. /. 2.,
    [b],
    [
      Link.{
        /* b */
        source: 0,
        /* f */
        target: {
          ancestorRoot: 2, /* 0 = b', 1 = e, 2 = g */
          absPath: [1 /* 1, 0 */],
        },
        linkRender: (~source, ~target) => {
          <>
            {if (debug_) {
               <> {drawBBox(source)} {drawBBox(target)} </>;
             } else {
               <> </>;
             }}
            <line
              x1={Js.Float.toString(source->Rectangle.x2)}
              y1={Js.Float.toString(source->Rectangle.cy)}
              x2={Js.Float.toString(target->Rectangle.x1)}
              y2={Js.Float.toString(target->Rectangle.cy)}
              stroke="purple"
            />
          </>;
        },
      },
    ],
  );

let c = str("4");
let c' = box(~dx=(12.5 -. 9.) /. 2. +. 2.5 /. 2., ~dy=2.5 /. 2., [c], []);

let d = str("/");
let d' = box(~dx=(12.5 -. 9.) /. 2. +. 2.5 /. 2., ~dy=2.5 /. 2., [d], []);

let e =
  seq(
    ~nodes=[a', b'],
    ~linkRender=(~source: _, ~target: _) => <> </>,
    ~gap=0.,
    ~direction=LeftRight,
  );

let f =
  seq(~nodes=[c', d'], ~linkRender=(~source, ~target) => <> </>, ~gap=0., ~direction=LeftRight);

let g =
  graph(
    ~nodes=[e, f],
    ~links=[],
    ~gap=25.,
    ~linkDistance=40.,
    ~constraints=directionConstraints(LeftRight),
  );