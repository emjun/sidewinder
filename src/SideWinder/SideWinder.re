/* namespace goodness */
module Util = Sidewinder_Util;
module Kernel = SideWinder_Kernel;
module LCA = SideWinder_LCA;
module Layout = SideWinder_Layout;
module RenderLinks = SideWinder_RenderLinks;
module Render = SideWinder_Render;

/* construct a node. links are turned into lcaLinks automatically for constraint layout */
let make = (~nodes, ~links, ~layout, ~computeSize, ~render): Kernel.node => {
  nodes,
  links: List.map(Link.sourceLocalToGlobal, links),
  layout,
  computeSize,
  render,
};

let render = (n: Kernel.node) =>
  n
  |> LCA.propagateLCA
  |> Layout.computeBBoxes
  |> RenderLinks.renderLinks
  |> Render.render
  |> ((Node.{rendered}) => rendered);

let debugLCA = (n: Kernel.node) => n |> LCA.propagateLCA |> Js.log;