let component = ReasonReact.statelessComponent("ChunksOverview");

module Styles = {
  open Css;

  let root =
    style([
      alignItems(`center),
      display(`flex),
      flexDirection(`column),
      fontSize(em(2.0)),
      height(`percent(100.0)),
      justifyContent(`center),
      position(`relative),
    ]);
  let arrow =
    style([
      position(`absolute),
      left(Theme.Space.double),
      top(Theme.Space.double),
    ]);
  let size = style([display(`block), color(Theme.Color.Text.secondary)]);
  let count = style([color(Theme.Color.Text.primary), margin(px(0))]);
  let diff = style([display(`block)]);
};

let make = (~size, ~count, _children) => {
  ...component,
  render: _self => {
    <section className=Styles.root>
      <PointingArrow className=Styles.arrow>
        {"Choose the" |> ReasonReact.string}
        <br />
        {"chunk here!" |> ReasonReact.string}
      </PointingArrow>
      <p className=Styles.count>
        {count
         |> Utils.pluralize(L10N.chunk, L10N.chunks)
         |> ReasonReact.string}
      </p>
      <Size className=Styles.size value={snd(size)} />
      <NumericDiff
        className=Styles.diff
        after={snd(size)}
        before={fst(size)}
      />
    </section>;
  },
};