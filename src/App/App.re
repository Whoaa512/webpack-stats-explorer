open State;

type action =
  | Next
  | Prev
  | Navigate(NavigationPath.Segment.t, int)
  | NavigateThroughBreadcrumbs(int)
  | UpdateComparisons(list(Compare.t));

let updateNavigationPath = (path: list('a), segment, depth): list('a) => {
  let tail = if (List.length(path) < depth) path else
    Belt.List.take(path, depth) |> Utils.defaultTo([]);

  [segment, ...(tail |> List.rev)] |> List.rev;
};

let component = ReasonReact.reducerComponent("App");

let reducer = (action, state) => switch (action) {
  | Next => ReasonReact.Update({
      index: (state.index + 1) mod List.length(state.comparisons),
      comparisons: state.comparisons,
      navigationPath: []
    })
  | Prev => ReasonReact.Update({
      index: (state.index - 1 + List.length(state.comparisons)) mod List.length(state.comparisons),
      comparisons: state.comparisons,
      navigationPath: []
    })
  | Navigate(segment, depth) => ReasonReact.Update({
    index: state.index,
    comparisons: state.comparisons,
    navigationPath: updateNavigationPath(state.navigationPath, segment, depth)
  })
  | NavigateThroughBreadcrumbs(index) => ReasonReact.Update({
    index: state.index,
    comparisons: state.comparisons,
    navigationPath: Belt.List.take(state.navigationPath, index) |> Utils.defaultTo([])
  })
  | UpdateComparisons(comparisons) => ReasonReact.Update({
    index: 0,
    comparisons: comparisons,
    navigationPath: []
  })
};

let compareStats = (stats) => stats
  |> Array.to_list
  |> List.sort((a: Stats.t, b: Stats.t) => a.builtAt - b.builtAt)
  |> List.fold_left((acc: (option(Stats.t), list(Compare.t)), a) =>
    switch(acc) {
    | (None, []) => (Some(a), [])
    | (Some(b), acc) => (Some(b), [Compare.make(b, a), ...acc])
    | _ => acc
    }, (None, [])
  )
  |> snd
  |> List.rev;

let make = (~comparisons, _children) => {
  ...component,

  initialState: () => {
    index: 0,
    comparisons: comparisons,
    navigationPath: [],
  },

  reducer,

  render: self => {
    let comp = List.nth(self.state.comparisons, self.state.index);
    let revPath = List.rev(self.state.navigationPath);

    let sideContent = NavigationPath.Segment.(switch (revPath) {
    | [(Item.Module(_leaf), kind), (Item.Chunk(chunk), _kind), ..._] => switch (chunk) {
      | Compare.Chunks.Summary(chunk) => <ModulesList
          modules=chunk.modules
          onModule=((sth) => self.send(Navigate(of_module(kind, Compare.Modules.Summary(sth)), 1)))
        />
      | Compare.Chunks.ModifiedSummary(chunk) => <ModulesCompare
          modules=chunk.modules
          onModule=((segment) => self.send(Navigate(segment, 1)))
        />
      }
    | [(Item.Module(leaf), kind), (Item.Module(parent), _kind2), ..._] => switch (parent) {
      | Compare.Modules.Summary(module_) => <ModulesList
          modules=module_.modules
          onModule=((sth) => self.send(Navigate(of_module(kind, Compare.Modules.Summary(sth)), 1)))
        />
      | Compare.Modules.ModifiedSummary(module_) => switch (module_.modules) {
        | Some(modules) => <ModulesCompare
            modules=modules
            onModule=((segment) => self.send(Navigate(segment, 1)))
          />
        | None => ReasonReact.null
        }
      }
    | _ => <ChunksCompare
        size=comp.size
        chunks=comp.chunks
        onChunk=((chunk) => self.send(Navigate(chunk, 0)))
      />
    });
    let mainContent = switch (revPath) {
      | [] => ReasonReact.null
      | segments => segments |> List.hd |> ((item, kind)) => switch (item) {
        | Chunk(chunk) => <ChunkSummary
            chunk=chunk
            kind=kind
            onModule=((module_) => self.send(Navigate(module_, 1)))
          />
        | Module(module_) => <ModuleSummary
            module_=module_
            kind=kind
            onModule=((module_) => self.send(Navigate(module_, 2)))
          />
        }
    };

    <Dropzone onStats=(stats => self.send(UpdateComparisons(compareStats(stats))))>
      <button onClick=(_ => self.send(Prev))>
        {ReasonReact.string("<<")}
      </button>
      {self.state.index + 1 |> string_of_int |> ReasonReact.string}
      {ReasonReact.string(" of ")}
      {self.state.comparisons |> List.length |> string_of_int |> ReasonReact.string}
      <button onClick=(_ => self.send(Next))>
        {ReasonReact.string(">>")}
      </button>
      <Breadcrumbs
        items=self.state.navigationPath
        onClick=(index => self.send(NavigateThroughBreadcrumbs(index)))
      />
      <NavigationLayout side=sideContent main=mainContent />
    </Dropzone>
  }
};
