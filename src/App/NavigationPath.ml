open Rationale.Option.Infix;;

module Segment = struct
  type t = CompareEntry.entry * CompareKind.t;;

  let make (kind : CompareKind.t) entry = (entry, kind);;

  let fromState (comp : CompareEntry.t) (id, kind) = CompareKind.(
    let entry (entry : Entry.t) = entry.id == id
    and modifiedEntry (entry : CompareEntry.t ModifiedEntry.t) = entry.id == id
    and createEntry entry = CompareEntry.Entry(entry)
    and createModifiedEntry entry = CompareEntry.ModifiedEntry(entry)
    and find predicate = Utils.List.findOpt predicate
    in
    match (kind) with
    | Added -> comp.added |> find entry <$> createEntry
    | Removed -> comp.removed |> find entry <$> createEntry
    | Intact -> comp.intact |> find entry <$> createEntry
    | Modified -> comp.modified |> find modifiedEntry <$> createModifiedEntry
  );;

  let toState (entry, kind) = State.NavigationPath.Segment.make kind entry;;
end

type t = Segment.t list;;

let rec fromState comp (statePath : State.NavigationPath.t) =
  match (statePath) with
  | [] -> []
  | (id, kind)::rest ->
      match (Segment.fromState comp (id, kind)) with
      | Some(entry) ->
        let segment = (entry, kind)
        in CompareEntry.(
          match (entry) with
          (* TODO: find out how to traverse children recursively *)
          | Entry(_) -> segment::[]
          | ModifiedEntry({ children }) -> segment::(fromState children rest)
        )
      | None -> fromState comp rest
;;
