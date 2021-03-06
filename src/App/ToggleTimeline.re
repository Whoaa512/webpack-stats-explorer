module Styles = {
  open Css;

  let arrow = style([display(`block)]);

  let up = style([transform(rotate(deg(90.0)))]);

  let down = style([transform(rotate(deg(-90.0)))]);
};

let arrow = {js|»|js};

[@react.component]
let make = (~className="", ~onToggle, ~isVisible) => {
  <Button onClick={_ => onToggle()}>
    <span
      className={Cn.make([Styles.arrow, isVisible ? Styles.down : Styles.up])}>
      {arrow |> React.string}
    </span>
  </Button>;
};